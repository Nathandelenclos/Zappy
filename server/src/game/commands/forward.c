/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** game/commands/forward.h
*/

#include "server.h"

/**
 * Forward cmd.
 * @param server - The server.
 * @param cmd - The cmd.
 */
void forward(server_t *server, cmd_t *cmd)
{
    client_t *client = cmd->client;
    int dir = client->player->direction;
    map_t *map = client->player->map;

    if (dir == NORTH) {
        put_in_list(&map->up->tile->items, client->player);
        client->player->map = map->up;
    }
    if (dir == SOUTH) {
        put_in_list(&map->down->tile->items, client->player);
        client->player->map = map->down;
    }
    if (dir == EAST) {
        put_in_list(&map->right->tile->items, client->player);
        client->player->map = map->right;
    }
    if (dir == WEST) {
        put_in_list(&map->left->tile->items, client->player);
        client->player->map = map->left;
    }
    delete_in_list(&map->tile->items, client->player);
    dprintf(client->socket_fd, "ok\n");
}
