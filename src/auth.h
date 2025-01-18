/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/


#ifndef AUTH_H
    #define AUTH_H
    #include <stdbool.h>
    #define SHADOW_FILE "/etc/shadow"
    #define ASK_PASS_PROMT "[my_sudo] password for %s: "


char *ask_pass(char *username);
bool check_pass(char *username, char *pass);
#endif /* AUTH_H */
