/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "auth.h"

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

// Return true if the password is right and false if error or bad password
bool check_pass(char *username, char *typed_pass)
{
    char *pass_hash;
    char *typed_hash;

    if (username == NULL || typed_pass == NULL)
        return false;
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
    printf(ASK_PASS_PROMT, username);
    tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
    getline(&buffer, &buffer_sz, stdin);
    tty.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
    write(STDOUT_FILENO, "\n", 1);
    buffer[strlen(buffer) - 1] = '\0';
    return buffer;
}
