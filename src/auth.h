/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/


#ifndef AUTH_H
    #define AUTH_H
    #include <stdbool.h>

//utils
    #define SHADOW_FILE "/etc/shadow"

bool check_pass(char *username, char *pass);
#endif /* AUTH_H */
