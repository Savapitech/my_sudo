/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#ifndef GROUP_H
    #define GROUP_H
    #define GROUP_FILE "/etc/group"
    #include <stdbool.h>
    #include <unistd.h>

typedef struct {
    size_t cap;
    size_t sz;
    gid_t *gids;
} gids_t;

int get_gid(char *group_name);
int get_primary_gid(char *username);
bool is_user_in_group(const char *group_name, const char *username);
bool get_user_groups(char *username, gids_t *gids);
#endif /* GROUP_H */
