/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** game/commands/left.h
*/

#include "server.h"

void left(server_t *server, cmd_t *cmd)
{
    client_t *client = cmd->client;
    int dir = client->player->direction;
    client->player->direction = (dir + 3) % 4;
    dprintf(client->socket_fd, "ok\n");
}
