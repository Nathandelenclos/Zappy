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
    add_items_to_inventory(&player->inventory, FOOD, FOOD_QUANTITY);
    player->level = 1;
    player->map = NULL;
    player->commands = NULL;
    player->alive = true;
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
    int index = 0;
    node *tmp = client->team->eggs_places;

    while (tmp != client->team->eggs_places) {
        index++;
        tmp = tmp->next;
    }
    remove_item_from_inventory(&place->tile->items, EGG);
    put_in_list(&place->tile->items, client->player);
    delete_in_list(&client->team->eggs_places, place);
    client->player->map = place;
    command_t command = {"eat", 126, eats};
    new_event(server, client, command);
    if (server->gui != NULL) {
        dprintf(server->gui->socket_fd, "pnw %d %d %d %d %d %s\n",
                client->socket_fd, client->player->map->pos_x,
                client->player->map->pos_y, client->player->direction,
                client->player->level, client->team->name);
        dprintf(server->gui->socket_fd, "ebo %d\n", index);
    }
}
