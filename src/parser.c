/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "group.h"
#include "user.h"

static
void switch_arg2(sf_t *sf, char *bin_name, char c)
{
    switch (c) {
        case 's':
            sf->flags |= S_FLAGS_SHELL;
            break;
        case 'h':
            print_usages(bin_name, S_EXIT_SUCCESS);
            break;
        case '?':
        default:
            print_usages(bin_name, S_EXIT_FAILURE);
    }
}

static
void switch_arg(sf_t *sf, char c, char *bin_name)
{
    switch (c) {
        case 'u':
            if (get_uid(optarg) == -1)
                exit((fprintf(stderr, "my_sudo: unknown user %s\n", optarg),
                    S_EXIT_FAILURE));
            sf->username = optarg;
            break;
        case 'g':
            if (get_gid(optarg) == -1)
                exit((fprintf(stderr, "my_sudo: unknown group %s\n", optarg),
                    S_EXIT_FAILURE));
            sf->group_name = optarg;
            break;
        case 'E':
            sf->flags |= S_FLAGS_ENV;
            break;
        default:
            switch_arg2(sf, bin_name, c);
    }
}

int parser(int ac, char **av, sf_t *sf)
{
    char c;

    if (ac < 2)
        print_usages(av[0], S_EXIT_FAILURE);
    for (c = getopt(ac, av, "u:g:Esh"); c != -1;
        c = getopt(ac, av, "u:g:Esh"))
            switch_arg(sf, c, av[0]);
    return optind;
}
