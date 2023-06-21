/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** map/generate.c
*/

#include "map.h"
#include "server.h"

/**
 * Place Random item on the map.
 * @param server - The server.
 * @param type - The type of the item.
 */
map_t *random_place(server_t *server, item_type_t type)
{
    int x = rand() % server->args->width;
    int y = rand() % server->args->height;
    map_t *tile = server->map;
    item_t *item = MALLOC(sizeof(item_t));
    item->type = type;
    for (int i = 0; i < x; i++)
        tile = tile->right;
    for (int i = 0; i < y; i++)
        tile = tile->down;
    put_in_list(&tile->tile->items, item);
    return tile;
}

node *random_places(server_t *server, item_type_t type, int quantity)
{
    node *places = NULL;
    for (int i = 0; i < quantity; ++i) {
        put_in_list(&places, random_place(server, type));
    }
    return places;
}

/**
 * Randomize the egg place.
 * @param server - The server.
 */
void randomize_egg(server_t *server)
{
    team_t *team;
    double quantity = server->args->clients_nb;
    for (node *tmp = server->teams; tmp; tmp = tmp->next) {
        double quantity_team = quantity;
        team = tmp->data;
        if (team->type == GUI) {
            continue;
        }
        while (quantity_team > 0) {
            put_in_list(&team->eggs_places, random_place(server, EGG));
            quantity_team--;
        }
    }
}

/**
 * Generate the map.
 * @param server - The server.
 */
void randomize_items(server_t *server)
{
    int total_case = server->args->width * server->args->height;
    for (int i = 0; type_density[i].type != PLAYER; ++i) {
        double quantity = total_case * type_density[i].density;
        while (quantity > 0) {
            random_place(server, type_density[i].type);
            quantity--;
        }
    }
    randomize_egg(server);
    command_t command = {"resource", 20, resource};
    new_event(server, NULL, command);
}
