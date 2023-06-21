/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** game/events/resource.h
*/

#include "server.h"

/**
 * Delete food item in inventory.
 * @param server - The server.
 * @param cmd - The cmd.
 */
void eats(server_t *server, cmd_t *cmd)
{
    client_t *client = cmd->client;
    if (get_item_count(client->player->inventory, FOOD) == 0) {
        dprintf(client->socket_fd, DEAD);
        client->player->alive = false;
        put_in_list(&client->team->eggs_places, client->player->map);
        add_item_to_inventory(&client->player->map->tile->items, EGG);
        delete_in_list(&client->player->map->tile->items, client);
        delete_in_list(&server->clients, client);
        return;
    }
    remove_item_from_inventory(&cmd->client->player->inventory, FOOD);
    command_t command = {"eat", 126, eats};
    new_event(server, cmd->client, command);
}
