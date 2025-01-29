/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "user.h"

// Return the username uid
int get_uid(char *username)
{
    FILE *file;
    char *buffer = NULL;
    size_t username_l;
    size_t buffer_sz;

    if (username == NULL)
        return -1;
    username_l = strlen(username);
    file = fopen(PASSWD_FILE, "r");
    if (file == NULL)
        return (fprintf(stderr, "Cannot open passwd file!\n"), -1);
    while (getline(&buffer, &buffer_sz, file) != -1) {
        if (strncmp(buffer, username, username_l) == 0) {
            buffer = strtok(buffer, ":");
            buffer = strtok(NULL, ":");
            buffer = strtok(NULL, ":");
            return (fclose(file), atoi(buffer));
        }
    }
    return (fclose(file), -1);
}

// Return the username gid
int get_gid(char *username)
{
    FILE *file;
    char *buffer = NULL;
    size_t username_l;
    size_t buffer_sz;

    username_l = strlen(username);
    file = fopen(PASSWD_FILE, "r");
    if (file == NULL)
        return (fprintf(stderr, "Cannot open passwd file!\n"), -1);
    while (getline(&buffer, &buffer_sz, file) != -1) {
        if (strncmp(buffer, username, username_l) == 0) {
            buffer = strtok(buffer, ":");
            buffer = strtok(NULL, ":");
            buffer = strtok(NULL, ":");
            buffer = strtok(NULL, ":");
            return (fclose(file), atoi(buffer));
        }
    }
    return (fclose(file), -1);
}

// Return the uid username
char *get_username(uid_t uid)
{
    FILE *file;
    char *buffer = NULL;
    size_t buffer_sz;
    char *user;
    char *uid_str;

    file = fopen(PASSWD_FILE, "r");
    if (file == NULL)
        return (fprintf(stderr, "Cannot open passwd file!\n"), NULL);
    while (getline(&buffer, &buffer_sz, file) != -1) {
        user = strtok(buffer, ":");
        strtok(NULL, ":");
        uid_str = strtok(NULL, ":");
        if (uid_str && (uid_t)strtoul(uid_str, NULL, 10) == uid)
            return (fclose(file), strdup(user));
    }
    return (fclose(file), NULL);
}

static
bool read_group_line(FILE *file, char *buffer, size_t size)
{
    if (fgets(buffer, size, file) == NULL)
        return false;
    return true;
}

static
bool parse_group_line(char *line, const char *group_name,
    const char *username)
{
    char *grp_name;
    char *members;
    char *member;

    grp_name = strtok(line, ":");
    strtok(NULL, ":");
    strtok(NULL, ":");
    members = strtok(NULL, "\n");
    if (!grp_name || strcmp(grp_name, group_name) != 0)
        return false;
    if (!members)
        return false;
    member = strtok(members, ",");
    while (member) {
        if (strcmp(member, username) == 0)
            return true;
        member = strtok(NULL, ",");
    }
    return false;
}

bool is_user_in_group(const char *group_name, const char *username)
{
    FILE *file;
    char line[512];

    if (*group_name == '\0' || *username == '\0')
        return false;
    file = fopen("/etc/group", "r");
    if (!file)
        return false;
    while (read_group_line(file, line, sizeof(line)))
        if (parse_group_line(line, group_name, username))
            return (fclose(file), true);
    return (fclose(file), false);
}

static
void add_group(char *line, char *username, gid_t *gids, size_t *ngids)
{
    __attribute__((unused)) char *group_name = strtok(line, ":");
    __attribute__((unused)) char *x = strtok(NULL, ":");
    char *gid_str = strtok(NULL, ":");
    char *members = strtok(NULL, "\n");
    gid_t gid;
    char *token;

    if (!gid_str || !members)
        return;
    gid = (gid_t)atoi(gid_str);
    token = strtok(members, ",");
    while (token) {
        if (strcmp(token, username) == 0) {
            gids[*ngids] = gid;
            (*ngids)++;
            break;
        }
        token = strtok(NULL, ",");
    }
}

static
bool check_gids_cap(gid_t **gids, size_t ngids, size_t *cap)
{
    gid_t *new_ptr;

    if (ngids == *cap - 1) {
        new_ptr = realloc(*gids, sizeof *gids * (*cap << 1));
        if (new_ptr == NULL)
            return false;
        *cap <<= 1;
        *gids = new_ptr;
    }
    return true;
}

bool get_user_groups(char *username, gids_t *gids)
{
    FILE *file;
    char line[512];

    gids->gids = calloc(gids->cap, sizeof(gid_t));
    if (gids == NULL)
        return false;
    if (username == NULL)
        return (free(gids), false);
    file = fopen("/etc/group", "r");
    if (!file)
        return (free(gids), NULL);
    while (read_group_line(file, line, sizeof(line))) {
        if (!check_gids_cap(&gids->gids, gids->sz, &gids->cap))
            return (fclose(file), false);
        add_group(line, username, gids->gids, &gids->sz);
    }
    return (fclose(file), true);
}
