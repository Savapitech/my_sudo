/*
** EPITECH PROJECT, 2024
** B-CPE-100-REN-1-1-cpoolday06-savinien.petitjean
** File description:
** Task 1
*/

#include "lib.h"

char *my_strupcase(char *str)
{
    for (int i = 0; str[i]; i++)
        if (islower(str[i]))
            str[i] -= 32;
    return (str);
}
