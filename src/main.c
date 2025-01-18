/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdio.h>
#include <unistd.h>

#include "auth.h"
#include "common.h"

int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
    char *username = getlogin();
    char *typed_pass = ask_pass(username);

    if (typed_pass == NULL)
        return S_EXIT_FAILURE;
    printf("Check pass result %b\n", check_pass(username, typed_pass));
}
