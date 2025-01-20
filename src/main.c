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

void print_usages(char *bin_name)
{
    printf("usage: %s -h\n"
        "usage: %s [-ugEs] [command [args ...]]\n", bin_name, bin_name);
    exit(S_EXIT_SUCCESS);
}

int main(int ac, char **av, char **env)
{
    char *username;
    char *typed_pass;
    uint8_t attempt = 0;
    sf_t sf;

    parser(ac, av, &sf);
    username = getlogin();
    for (; attempt < 3; attempt++) {
        typed_pass = ask_pass(username);
        if (typed_pass == NULL)
            return S_EXIT_FAILURE;
        if (check_pass(username, typed_pass))
            execute_as(av[1], av + 1, env, 0);
        else
            fprintf(stderr, "Sorry, try again.\n");
    }
    if (attempt)
        fprintf(stderr, "my_sudo: %u incorrect password attempt\n", attempt);
}
