/*
** EPITECH PROJECT, 2023
**
** File description:
**
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "cmd.h"

typedef struct server_s server_t;
typedef struct client_s client_t;
typedef char *string;

void debug_cmd(server_t *server, cmd_t *cmd);

#endif
