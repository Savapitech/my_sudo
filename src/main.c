/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "auth.h"
#include "common.h"
#include "exec.h"
#include "user.h"

void print_usages(char *bin_name, uint8_t exit_code)
{
    printf("usage: %s -h\n"
        "usage: %s [-ugEs] [command [args ...]]\n", bin_name, bin_name);
    exit(exit_code);
}

static
int my_sudo(sf_t *sf)
{
    char *launching_username = getlogin();
    char *typed_pass;
    uint8_t attempt = 0;

    for (; attempt < 3; attempt++) {
        typed_pass = ask_pass(launching_username);
        if (typed_pass == NULL)
            return S_EXIT_FAILURE;
        if (check_pass(launching_username, typed_pass))
            break;
        fprintf(stderr, "Sorry, try again.\n");
    }
    if (attempt) {
        fprintf(stderr, "my_sudo: %u incorrect password attempt%s\n",
            attempt, attempt > 1 ? "s" : "");
        if (attempt > 2)
            return S_EXIT_FAILURE;
    }
    execute_as(sf->args[sf->optindex], sf, get_uid(sf->username));
    return S_EXIT_SUCCESS;
}

int main(int ac, char **av, char **env)
{
    sf_t sf = { 0, .args = av, .env = env };

    sf.optindex = parser(ac, av, &sf);
    if (!(sf.optindex < ac))
        print_usages(av[0], S_EXIT_FAILURE);
    if (my_sudo(&sf) == S_EXIT_FAILURE)
        return S_EXIT_FAILURE;
    return S_EXIT_SUCCESS;
}
