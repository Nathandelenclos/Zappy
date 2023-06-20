/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** game/new_player.h
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
    player->direction = rand() % 4;
    player->inventory = NULL;
    add_items_to_inventory(&player->inventory, FOOD, 10);
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
    map_t *place = client->team->eggs_places->data;
    remove_item_from_inventory(&place->tile->items, EGG);
    put_in_list(&place->tile->items, client->player);
    delete_in_list(&client->team->eggs_places, place);
    client->player->map = place;
    command_t command = {"eat", 126, eats};
    new_command(server, client, command, "start");
}
