/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** utils/player_to_client.c
*/

#include "server.h"

/**
 * Get the clients from the players.
 * @param server - The server.
 * @param players - The players.
 * @return The clients.
 */
node *player_to_client(server_t *server, node *players)
{
    node *clients = NULL;
    player_t *tmp_player;
    for (node *tmp = players; tmp; tmp = tmp->next) {
        tmp_player = tmp->data;
        for (node *tmp_c = server->clients; tmp_c; tmp_c = tmp_c->next) {
            if (!search_by_player(tmp_c->data, tmp_player)) {
                put_in_list(&clients, tmp_c->data);
            }
        }
    }
    return clients;
}

