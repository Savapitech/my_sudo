/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdbool.h>
#include <unistd.h>

bool execute_as(char *bin, char const *arg, uid_t uid)
{
    if (setuid(uid) == -1)
        return false;
    execlp(bin, arg);
    return true;
}
