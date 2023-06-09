/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** game/commands/left.c
*/

#include "server.h"

/**
 * Left cmd.
 * @param server - The server.
 * @param cmd - The cmd.
 */
void left(server_t *server, cmd_t *cmd)
{
    client_t *client = cmd->client;
    int dir = client->player->direction;
    client->player->direction = (dir + 1) % 4;
    dprintf(client->socket_fd, OK);
}
