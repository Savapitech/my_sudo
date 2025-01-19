/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "auth.h"
#include "common.h"
#include "exec.h"

static
void print_usages(char *bin_name)
{
    printf("usage: %s -h\n"
        "usage: %s [-ugEs] [command [args ...]]\n", bin_name, bin_name);
}

int main(int ac, char **av, char **env)
{
    char *username;
    char *typed_pass;

    if (ac < 2 || strcmp(av[1], "-h") == 0)
        return (print_usages(av[0]), S_EXIT_SUCCESS);
    username = getlogin();
    printf("Username: %s", username);
    typed_pass = ask_pass(username);
    if (typed_pass == NULL)
        return S_EXIT_FAILURE;
    printf("Typed pass: %s", typed_pass);
    if (check_pass(username, typed_pass))
        execute_as(av[1], av + 1, env, 0);
    printf("Check pass result %b\n", check_pass(username, typed_pass));
}
