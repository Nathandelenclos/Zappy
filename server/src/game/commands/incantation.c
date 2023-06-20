/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** network/actions.c
*/

#include "server.h"

/**
 * Get the players on the tile.
 * @param server - The server.
 * @param cmd - The cmd.
 * @return The players.
 */
node *get_players_on_tile(cmd_t *cmd)
{
    node *players = NULL;
    node *tmp = cmd->client->player->map->tile->items;
    item_t *item = NULL;
    while (tmp) {
        item = tmp->data;
        if (item->type == PLAYER) {
            put_in_end(&players, item);
        }
        tmp = tmp->next;
    }
    return players;
}

node *get_players_on_tile_with_level(cmd_t *cmd, int level)
{
    node *players = get_players_on_tile(cmd);
    node *players_level = NULL;
    node *tmp = players;
    player_t *player = NULL;
    while (tmp) {
        player = tmp->data;
        if (player->level == level) {
            put_in_end(&players_level, player);
        }
        tmp = tmp->next;
    }
    return players_level;
}

/**
 * Check if the incantation is possible.
 * @param cmd - The cmd.
 * @return - True if possible, false otherwise.
 */
bool check_incantation(cmd_t *cmd)
{
    node *items = cmd->client->player->map->tile->items;
    player_t *player = cmd->client->player;
    int level = player->level;
    node *players = get_players_on_tile(cmd);
    player_t *tmp_player;
    int player_count = 0;
    for (node *tmp = players; tmp; tmp = tmp->next) {
        tmp_player = tmp->data;
        if (tmp_player->level == level) {
            player_count++;
        }
    }
    if (evolutions[level][0] > player_count) {
        return false;
    }
    for (int i = 1; i < 8; ++i) {
        if (evolutions[level][i] > get_item_count(items, i)) {
            return false;
        }
    }
    return true;
}

/**
 * Incantation cmd.
 * @param server - The server.
 * @param cmd - The cmd.
 */
void incantation(server_t *server, cmd_t *cmd)
{
    if (check_incantation(cmd)) {
        node *players = get_players_on_tile_with_level(cmd,
            cmd->client->player->level);
        for (node *tmp = players; tmp; tmp = tmp->next)
            ((player_t *)tmp->data)->level++;
        dprintf(cmd->client->socket_fd, "Current level: %d\n",
            cmd->client->player->level);
    } else {
        dprintf(cmd->client->socket_fd, KO);
    }
}

/**
 * Incantation start cmd.
 * @param server - The server.
 * @param cmd - The cmd.
 */
void incantation_start(server_t *server, cmd_t *cmd)
{
    if (check_incantation(cmd)) {
        node *players = get_players_on_tile_with_level(cmd,
            cmd->client->player->level);
        for (node *tmp = players; tmp; tmp = tmp->next) {
            node *client = search_in_list_by(server->clients, tmp->data,
                search_by_player);
            dprintf(((client_t *)client->data)->socket_fd, "Elevation underway\n");
        }
        command_t end = {"incantation_end", 300, incantation};
        new_command(server, cmd->client, end, cmd->cmd);
    } else {
        dprintf(cmd->client->socket_fd, KO);
    }
}
