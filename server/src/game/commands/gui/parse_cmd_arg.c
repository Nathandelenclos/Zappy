/*
** EPITECH PROJECT, 2023
** server
** File description:
** parse_cmd_arg.c
*/

#include "server.h"
#include <ctype.h>

/**
 * Parse the command arguments.
 * @param cmd - The command.
 * @return int - 0 if success, -1 otherwise.
 */
int parse_cmd_arg(char *cmd, bool first_use)
{
    char *tmp = first_use ? my_strdup(cmd) : NULL;
    int res = 0;
    char *token = strtok(first_use ? tmp : NULL, " \0");
    char *ptr;

    if (token == NULL)
        return -1;
    long conversion = strtol(token, &ptr, 10);
    if (conversion == 0 && (ptr == token || *ptr != '\0')) {
        return -1;
    }
    res = atoi(token);
    return res;
}
