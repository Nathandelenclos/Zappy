/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** network/actions.c
*/

#include "server.h"

void incantation(server_t *server, cmd_t *cmd)
{
    dprintf(cmd->client->socket_fd, "test end\n");
}

void incantation_start(server_t *server, cmd_t *cmd)
{
    dprintf(cmd->client->socket_fd, "test start\n");
}
