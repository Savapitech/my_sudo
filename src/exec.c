/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#define _GNU_SOURCE
#include <stdbool.h>
#include <unistd.h>

bool execute_as(char *bin, char **args, char **env, uid_t uid)
{
    if (setuid(uid) == -1)
        return false;
    execvpe(bin, args, env);
    return true;
}
