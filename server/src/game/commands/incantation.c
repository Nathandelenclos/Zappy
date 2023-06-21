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
    int level = player->level;
    node *players = get_players_on_tile_with_level(cmd,
        cmd->client->player->level);
    if (evolutions[level - 1][0] > len_list(players)) {
        return false;
    }
    for (int i = 1; i < 8; ++i) {
        if (evolutions[level - 1][i] > get_item_count(items, i)) {
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
    node *players = get_players_on_tile_with_level(cmd,
        cmd->client->player->level);
    node *clients = player_to_client(server, players);
    client_t *tmp_client;
    if (check_incantation(cmd)) {
        for (node *tmp = clients; tmp; tmp = tmp->next) {
            tmp_client = tmp->data;
            tmp_client->player->level++;
            dprintf(tmp_client->socket_fd, "Current level: %d\n",
                tmp_client->player->level);
        }
        if (server->gui != NULL) {
            dprintf(server->gui->socket_fd, "pie %d %d 1\n",
                cmd->client->player->map->pos_x,
                cmd->client->player->map->pos_y);
        }
    } else {
        for (node *tmp = clients; tmp; tmp = tmp->next) {
            tmp_client = tmp->data;
            dprintf(tmp_client->socket_fd, KO);
        }
    }
}

/**
 * Incantation error cmd.
 * @param server - The server.
 * @param cmd - The cmd.
 */
void incantation_error(server_t *server, cmd_t *cmd)
{
    dprintf(cmd->client->socket_fd, KO);
}

/**
 * Incantation mate cmd.
 * @param server - The server.
 * @param cmd - The cmd.
 */
void incantation_mate(server_t *server, cmd_t *cmd)
{
    node *player = NULL;
    put_in_list(&player, cmd->client);
    resume_activity(server, player);
    FREE(player);
}

/**
 * Incantation start cmd.
 * @param server - The server.
 * @param cmd - The cmd.
 */
void incantation_start(server_t *server, cmd_t *cmd)
{
    void (*func)(server_t *server, struct cmd_s *cmd);
    command_t mate = {"incantation_mate", 300, incantation_mate};
    client_t *client_tmp;
    if (check_incantation(cmd)) {
        if (server->gui != NULL) {
            dprintf(server->gui->socket_fd, "pic %d %d %d",
                cmd->client->player->map->pos_x, cmd->client->player->map->pos_y,
                cmd->client->player->level);
        }
        node *players = get_players_on_tile_with_level(cmd,
            cmd->client->player->level);
        node *clients = player_to_client(server, players);
        for (node *tmp = clients; tmp; tmp = tmp->next) {
            node *client_mate = NULL;
            client_tmp = tmp->data;
            if (cmd->client == client_tmp) {
                continue;
            }
            put_in_list(&client_mate, client_tmp);
            pause_activity(server, client_mate);
            FREE(client_mate);
            if (server->gui != NULL) {
                dprintf(server->gui->socket_fd, " %d",
                    client_tmp->socket_fd);
            }
            dprintf(client_tmp->socket_fd, ELEVATION_UNDERWAY);
            new_command(server, client_tmp, mate, "incantation_mate");
        }
        dprintf(cmd->client->socket_fd, ELEVATION_UNDERWAY);
        func = incantation;
    } else {
        func = incantation_error;
        dprintf(cmd->client->socket_fd, KO);
    }
    command_t end = {"incantation_end", 300, func};
    new_command(server, cmd->client, end, cmd->cmd);
}
