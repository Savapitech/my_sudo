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

#include "common.h"

uid_t get_uid(char *username)
{
    FILE *file;
    char *buffer;
    size_t username_l;
    size_t buffer_sz;
    uid_t result = 0;

    if (username == NULL)
        return S_EXIT_FAILURE;
    username_l = strlen(username);
    if (!username_l)
        return S_EXIT_FAILURE;
    file = fopen("/etc/passwd", "r");
    if (file == NULL)
        return S_EXIT_FAILURE;
    while (getline(&buffer, &buffer_sz, file)) {
        if (strncmp(buffer, username, username_l) == 0) {
            buffer += 2;
            buffer += strcspn(buffer, ":");
            return atoi(buffer);
        }
    }
    return result;
}
