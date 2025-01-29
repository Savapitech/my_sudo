/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#ifndef USER_H
    #define USER_H
    #define PASSWD_FILE "/etc/passwd"
    #include <stdbool.h>
    #include <unistd.h>

int get_uid(char *username);
char *get_username(uid_t uid);
#endif /* USER_H */
