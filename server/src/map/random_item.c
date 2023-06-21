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
void random_place(server_t *server, item_type_t type)
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
}
