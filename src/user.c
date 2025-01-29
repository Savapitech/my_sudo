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
    size_t buffer_sz;

    if (username == NULL)
        return -1;
    file = fopen(PASSWD_FILE, "r");
    if (file == NULL)
        return (fprintf(stderr, "Cannot open passwd file!\n"), -1);
    while (getline(&buffer, &buffer_sz, file) != -1) {
        buffer = strtok(buffer, ":");
        if (buffer == NULL)
            continue;
        if (strcmp(buffer, username) == 0) {
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
