/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#ifndef COMMON_H
    #define COMMON_H
    #define S_EXIT_SUCCESS 0
    #define S_EXIT_FAILURE 84
    #include <stdint.h>

typedef struct {
    uint8_t flags;
    char *username;
} sf_t;


// utils
int stridx(char const *str, char c);

int parser(int ac, char **av, sf_t *sf);
void print_usages(char *bin_name, uint8_t exit_code);
#endif /* COMMON_H */
