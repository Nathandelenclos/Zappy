/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** network/actions.c
*/

#include "server.h"


void eject(server_t *server, cmd_t *cmd)
{
    if (get_item_count(cmd->client->player->map->tile->items, EGG) >= 1) {
        remove_item_from_inventory(&cmd->client->player->map->tile->items, EGG);
    }
    dprintf(cmd->client->socket_fd, OK);
}
