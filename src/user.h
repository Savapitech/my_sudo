/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#ifndef USER_H
    #define USER_H
    #define PASSWD_FILE "/etc/passwd"
    #define GROUP_FILE "/etc/group"
    #include <stdbool.h>
    #include <unistd.h>

int get_uid(char *username);
char *get_username(uid_t uid);
bool is_user_in_group(const char *group_name, const char *username);
#endif /* USER_H */
