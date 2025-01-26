/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    file = fopen("/etc/passwd", "r");
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

    file = fopen("/etc/passwd", "r");
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
