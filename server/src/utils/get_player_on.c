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

/**
 * Get the players on the tile with the level.
 * @param server - The server.
 * @param cmd - The cmd.
 * @param level - The level.
 * @return The players.
 */
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
