/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#ifndef EXEC_H
    #define EXEC_H
    #include <stdbool.h>
    #include <unistd.h>

bool execute_as(char *bin, char **args, char **env, uid_t uid);
#endif /* EXEC_H */
