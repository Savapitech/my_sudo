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
    while (getline(&buffer, &buffer_sz, file)) {
        if (strncmp(buffer, username, username_l) == 0) {
            buffer = strtok(buffer, ":");
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
    while (getline(&buffer, &buffer_sz, file)) {
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
    if (fgets(buffer, size, file) == NULL) {
        return false;
    }
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
