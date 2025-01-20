/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stddef.h>

__attribute__((const))
int stridx(char const *str, char c)
{
    int i = 0;

    if (str == NULL)
        return -1;
    for (; str[i] != '\0'; i++)
        if (str[i] == c)
            return i;
    return -1;
}
