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

// Replace the actual process with the bin pointed process as the specified uid
bool execute_as(char *bin, sf_t *sf, int uid)
{
    int gid = 0;
    gids_t gids = { .cap = 4, 0 };

    uid = uid == -1 ? 0 : uid;
    gid = uid == -1 ? 0 : gid;
    if (uid == 0) {
        setgid(0);
        setgroups(1, &(gid_t){ 0 });
    } else {
        if (!get_user_groups(sf->username, &gids))
            return false;
        if (gids.gids == NULL)
            return false;
        setgroups(gids.sz, gids.gids);
        setgid(get_gid(sf->username));
        free(gids.gids);
    }
    if (setuid(uid) == -1)
        return false;
    return exec_with_uid_gids(sf, bin);
}
