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

bool execute_as(char *bin, sf_t *sf, int uid)
{
    uid = uid == -1 ? 0 : uid;
    if (setuid(uid) == -1)
        return false;
    execvpe(bin, sf->args + sf->optindex, sf->env);
    return true;
}
