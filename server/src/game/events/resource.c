/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** message.h
*/

#include "server.h"

/**
 * Get actual density.
 * @param server - The server.
 * @param item_type - The item type.
 * @return - The density.
 */
double get_actual_density(server_t *server, item_type_t item_type)
{
    double quantity = 0;
    map_t *map = server->map;
    for (int i = 0; i < server->args->width; ++i) {
        for (int j = 0; j < server->args->height; ++j) {
            quantity += get_item_count(map->tile->items, item_type);
            map = map->down;
        }
        map = map->right;
    }
    return quantity / (server->args->width * server->args->height);
}

/**
 * Handle resource.
 * @param server - The server.
 * @param cmd - The cmd.
 */
void resource(server_t *server, cmd_t *cmd)
{
    for (int i = 0; type_density[i].type != PLAYER; ++i) {
        double actual_density = get_actual_density(server, type_density[i].type);
        double needed_density = type_density[i].density;
        double diff = needed_density - actual_density;
        if (diff > 0) {
            double quantity = diff * (server->args->width * server->args->height);
            random_places(server, type_density[i].type, (int)quantity);
        }
    }
    dprintf(1, "Map generated\n");
    command_t command = {"resource", 20, resource};
    new_event(server, NULL, command);
}
