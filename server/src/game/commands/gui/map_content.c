/*
** EPITECH PROJECT, 2023
** server
** File description:
** map_content.c
*/
#include "server.h"

/**
 * Get the map size.
 * @param server - The server.
 * @param cmd - The command.
 */
void msz(server_t *server, cmd_t *cmd)
{
    dprintf(cmd->client->socket_fd, "msz %d %d\n",
            server->map_width, server->map_height);
}

void mct(server_t *server, cmd_t *cmd)
{
    for (int y = 0; y < server->map_height; y++) {
        for (int x = 0; x < server->map_width; x++) {
        }
    }
}