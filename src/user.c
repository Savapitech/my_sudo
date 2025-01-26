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
