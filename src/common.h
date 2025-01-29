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

enum {
    S_FLAGS_SHELL = 1 << 0,
    S_FLAGS_ENV = 1 << 1
};

typedef struct {
    uint8_t flags;
    char *username;
    char *launching_user;
    char *group_name;
    char **args;
    char **env;
    int optindex;
} sf_t;

// utils
int stridx(char const *str, char c);

int parser(int ac, char **av, sf_t *sf);
void print_usages(char *bin_name, uint8_t exit_code);
#endif /* COMMON_H */
