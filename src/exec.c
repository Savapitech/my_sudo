/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#define _GNU_SOURCE
#include <errno.h>
#include <grp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common.h"
#include "group.h"
#include "user.h"

static
bool exec_with_uid_gids(sf_t *sf, char *bin)
{
    char *shell;

    if (sf->flags & S_FLAGS_SHELL) {
        shell = getenv("SHELL");
        if (shell != NULL)
            execve(shell, sf->args + sf->optindex, sf->env);
        return (fprintf(stderr, "Cannot find SHELL !\n"), false);
    }
    execvpe(bin, sf->args + sf->optindex, sf->env);
    if (errno && errno == ENOENT)
        fprintf(stderr, "my_sudo: %s: command not found\n", bin);
    return true;
}

static
bool set_gids(sf_t *sf)
{
    int gid = 0;
    gids_t gids = { .cap = 4, 0 };

    if (!get_user_groups(sf->username, &gids))
        return false;
    if (sf->group_name != NULL) {
        gid = get_gid(sf->group_name);
        if (gids.sz == gids.cap -2)
            check_gids_cap(&gids.gids, gids.sz, &gids.cap);
        gids.gids[gids.sz] = get_primary_gid(sf->username);
        gids.sz++;
    } else
        gid = get_primary_gid(sf->username);
    if (gids.gids == NULL)
        return false;
    setgid(gid);
    setgroups(gids.sz, gids.gids);
    free(gids.gids);
    return true;
}

// Replace the actual process with the bin pointed process as the specified uid
bool execute_as(char *bin, sf_t *sf)
{
    if (sf->username == NULL && sf->group_name == NULL)
        sf->username = "root";
    else if (sf->username == NULL && sf->group_name != NULL)
        sf->username = sf->launching_user;
    if (set_gids(sf) == false)
        return false;
    if (setuid(get_uid(sf->username)) == -1)
        return false;
    return exec_with_uid_gids(sf, bin);
}
