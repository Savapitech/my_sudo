/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "auth.h"
#include "common.h"
#include "group.h"
#include "user.h"

static
char *parse_shadow_line(char *buffer, size_t username_l)
{
    if (strlen(buffer) < username_l + 10)
        return NULL;
    buffer += username_l + 1;
    buffer[strcspn(buffer, ":")] = '\0';
    return buffer;
}

static
char *get_pass_hash(char *username)
{
    FILE *file = fopen(SHADOW_FILE, "ro");
    char *buffer = NULL;
    size_t buffer_sz = 128;
    size_t username_l = strlen(username);

    if (file == NULL)
        return (fprintf(stderr, "Cannot open shadow file "
            "(insufficient permissions ?)\n"), NULL);
    if (username_l < 1)
        return (fclose(file), NULL);
    for (; getline(&buffer, &buffer_sz, file) != -1;)
        if (strncmp(buffer, username, username_l) == 0)
            return (fclose(file), parse_shadow_line(buffer, username_l));
    free(buffer);
    return (fclose(file), NULL);
}

static
bool check_sudoers_line(char *username, char *buffer, size_t username_l)
{
    char *gid;

    if (strncmp(buffer, username, username_l) == 0)
        return true;
    buffer[strcspn(buffer, " ")] = '\0';
    if (*buffer == '%' && is_user_in_group(buffer + 1, username))
        return true;
    if (*buffer == '#' && isdigit(*(buffer + 1))) {
        asprintf(&gid, "%u", get_uid(username));
        if (gid == NULL)
            return false;
        if (strncmp(gid, buffer + 1, strlen(gid)) == 0)
            return (free(gid), true);
    }
    return false;
}

static
bool check_sudoers(char *username)
{
    FILE *file = fopen(SUDOERS_FILE, "ro");
    char *buffer = NULL;
    size_t buffer_sz = 128;
    size_t username_l = strlen(username);

    if (file == NULL)
        return (fprintf(stderr, "Cannot open sudoer file "
            "(insufficient permissions ?)\n"), false);
    if (username_l < 1)
        return (fclose(file), false);
    for (; getline(&buffer, &buffer_sz, file) != -1;)
        if (check_sudoers_line(username, buffer, username_l) == true)
            return (fclose(file), true);
    free(buffer);
    return (fclose(file), false);
}

// Return true if the password is right and false if error or bad password
bool check_pass(char *username, char *typed_pass)
{
    char *pass_hash;
    char *typed_hash;

    if (username == NULL || typed_pass == NULL)
        return false;
    if (!check_sudoers(username))
        exit((fprintf(stderr, "%s is not in the sudoers file.\n", username),
            S_EXIT_FAILURE));
    pass_hash = get_pass_hash(username);
    if (pass_hash == NULL)
        return false;
    typed_hash = crypt(typed_pass, pass_hash);
    if (strcmp(typed_hash, pass_hash) == 0)
        return true;
    return false;
}

// Launch a mini repl to get the user input without echo the typed chars
char *ask_pass(char *username)
{
    char *buffer = NULL;
    size_t buffer_sz = 128;
    struct termios tty;

    if (username == NULL)
        return NULL;
    if (tcgetattr(STDIN_FILENO, &tty) == -1)
        return NULL;
    printf("[my_sudo] password for %s: ", username);
    tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
    getline(&buffer, &buffer_sz, stdin);
    tty.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
    write(STDOUT_FILENO, "\n", 1);
    buffer[strlen(buffer) - 1] = '\0';
    return buffer;
}
