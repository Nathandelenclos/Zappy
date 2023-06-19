/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** network/actions.c
*/

#include "server.h"

/**
 * Check if the incantation is possible.
 * @param cmd - The cmd.
 * @return - True if possible, false otherwise.
 */
bool check_incantation(cmd_t *cmd)
{
    node *items = cmd->client->player->map->tile->items;
    player_t *player = cmd->client->player;
    for (int i = 0; i < 8; ++i) {
        if (evolutions[player->level - 1][i] > get_item_count(items, i)) {
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
        cmd->client->player->level++;
        dprintf(cmd->client->socket_fd, OK);
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
        dprintf(cmd->client->socket_fd, "Elevation underway\n");
        command_t end = {"incantation_end", 300, incantation};
        new_command(server, cmd->client, end, cmd->cmd);
    } else {
        dprintf(cmd->client->socket_fd, KO);
    }
}
