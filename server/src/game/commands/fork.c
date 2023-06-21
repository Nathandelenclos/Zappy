/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** game/commands/forward.c
*/

#include "server.h"

/**
 * Create a new egg.
 * @param server - The server.
 * @param cmd - The cmd.
 */
void fork_cmd(server_t *server, cmd_t *cmd)
{
    client_t *client = cmd->client;
    player_t *player = cmd->client->player;

    put_in_list(&client->team->eggs_places, player->map);
    add_item_to_inventory(&player->map->tile->items, EGG);
    dprintf(client->socket_fd, OK);
    if (server->gui != NULL)
        dprintf(server->gui->socket_fd, "enw %d %d %d %d\n",
        0, client->socket_fd,
        player->map->pos_x, player->map->pos_y);
}
