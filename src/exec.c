/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#define _GNU_SOURCE
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common.h"


// Replace the actual process with the bin pointed process as the specified uid
bool execute_as(char *bin, sf_t *sf, int uid)
{
    char *shell;

    uid = uid == -1 ? 0 : uid;
    if (setuid(uid) == -1)
        return false;
    if (sf->flags & S_FLAGS_SHELL) {
        shell = getenv("SHELL");
        if (shell != NULL)
            execve(shell, sf->args + sf->optindex, sf->env);
    }
    if (sf->flags & S_FLAGS_ENV)
        execvpe(bin, sf->args + sf->optindex, sf->env);
    else
        execvp(bin, sf->args + sf->optindex);
    if (errno && errno == ENOENT)
        fprintf(stderr, "my_sudo: %s: command not found\n", bin);
    return true;
}
