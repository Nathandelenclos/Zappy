/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** message.h
*/

#include "server.h"
#include <stdlib.h>

/**
 * Create a player.
 * @return player_t * - The player.
 */
player_t *create_player()
{
    player_t *player = MALLOC(sizeof(player_t));
    player->type = PLAYER;
    player->inventory = NULL;
    player->level = 1;
    player->map = NULL;
    player->commands = NULL;
    return player;
}

/**
 * Create a new player.
 * @param server - The server.
 * @param client - The client.
 */
void new_player(server_t *server, client_t *client)
{
    client->player = create_player();
    map_t *map = server->map;
    int x = rand() % server->args->width;
    int y = rand() % server->args->height;
    for (int i = 0; i < x; ++i) {
        map = map->right;
    }
    for (int i = 0; i < y; ++i) {
        map = map->down;
    }
    put_in_list(&map->tile->items, client->player);
    client->player->map = map;
}
