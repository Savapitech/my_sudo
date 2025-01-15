/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdlib.h>
#include <unistd.h>

#include "exec.h"

int main(int ac, char **av)
{
    if (ac < 2)
        return EXIT_FAILURE;
    execute_as(av[1], av[2], 0);
}
