/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#define _GNU_SOURCE
#include <stdbool.h>
#include <unistd.h>

#include "common.h"


// Replace the actual process with the bin pointed process as the specified uid
bool execute_as(char *bin, sf_t *sf, int uid)
{
    uid = uid == -1 ? 0 : uid;
    if (setuid(uid) == -1)
        return false;
    if (sf->flags & S_FLAGS_ENV)
        execvpe(bin, sf->args + sf->optindex, sf->env);
    else
        execvp(bin, sf->args + sf->optindex);
    return true;
}
