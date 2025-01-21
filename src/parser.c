/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <getopt.h>

#include "common.h"

static
void switch_arg(sf_t *sf, char c, char *bin_name)
{
    switch (c) {
        case 'u':
            sf->username = optarg;
            break;
        case 'h':
            print_usages(bin_name, S_EXIT_SUCCESS);
            break;
        case '?':
        default:
            print_usages(bin_name, S_EXIT_FAILURE);
    }
}

int parser(int ac, char **av, sf_t *sf)
{
    char c;

    if (ac < 2)
        print_usages(av[0], S_EXIT_FAILURE);
    for (c = getopt(ac, av, "u:g:E:s:h"); c != -1;
        c = getopt(ac, av, "u:g:E:s:h"))
            switch_arg(sf, c, av[0]);
    return S_EXIT_SUCCESS;
}
