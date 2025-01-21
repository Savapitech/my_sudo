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

void print_usages(char *bin_name, uint8_t exit_code)
{
    printf("usage: %s -h\n"
        "usage: %s [-ugEs] [command [args ...]]\n", bin_name, bin_name);
    exit(exit_code);
}

static
int my_sudo(char **av, char **env)
{
    char *username = getlogin();
    char *typed_pass;
    uint8_t attempt = 0;

    for (; attempt < 3; attempt++) {
        typed_pass = ask_pass(username);
        if (typed_pass == NULL)
            return S_EXIT_FAILURE;
        if (check_pass(username, typed_pass))
            break;
        (sleep((rand() % 2) + 1), fprintf(stderr, "Sorry, try again.\n"));
    }
    if (attempt) {
        fprintf(stderr, "my_sudo: %u incorrect password attempt%s\n",
            attempt, attempt > 1 ? "s" : "");
        if (attempt > 2)
            return S_EXIT_FAILURE;
    }
    execute_as(av[1], av + 1, env, 0);
    return S_EXIT_SUCCESS;
}

int main(int ac, char **av, char **env)
{
    sf_t sf;

    parser(ac, av, &sf);
    if (my_sudo(av, env) == S_EXIT_FAILURE)
        return S_EXIT_FAILURE;
    return S_EXIT_SUCCESS;
}
