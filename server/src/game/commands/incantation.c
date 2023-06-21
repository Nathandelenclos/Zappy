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
 * Pause current activity.
 * @param server - The server.
 * @param clients - The clients.
 */
void pause_activity(server_t *server, node *clients)
{
    client_t *client;
    for (node *tmp = clients; tmp; tmp = tmp->next) {
        client = tmp->data;
        cmd_t *last_command = client->commands->data;
        if (last_command->state == STARTED) {
            last_command->state = PAUSE;
            last_command->timestamp_end = server->time;
            delete_in_list(&server->cmd_queue, last_command);
        }
    }
}

/**
 * Resume current activity.
 * @param server - The server.
 * @param clients - The clients.
 */
void resume_activity(server_t *server, node *clients)
{
    client_t *client;
    for (node *tmp = clients; tmp; tmp = tmp->next) {
        client = tmp->data;
        cmd_t *cmd_tmp;
        for (node *node_cmd = client->commands; node_cmd; node_cmd = node_cmd->next) {
            cmd_tmp = node_cmd->data;
            if (cmd_tmp->state == PAUSE) {
                cmd_tmp->state = STARTED;
                timestamp_t diff =
                    cmd_tmp->timestamp_end - cmd_tmp->timestamp_start;
                timestamp_t need_time = (cmd_tmp->ticks != 0 ?
                    (((cmd_tmp->ticks * 1000) / server->args->freq)) : 0);
                cmd_tmp->timestamp_end = server->time + (need_time - diff);
                add_cmd(cmd_tmp, &server->cmd_queue);
                break;
            }
        }
    }
}

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
            dprintf(client_tmp->socket_fd, "Elevation underway\n");
            new_command(server, client_tmp, mate, "incantation_mate");
        }
        dprintf(cmd->client->socket_fd, "Elevation underway\n");
        func = incantation;
    } else {
        func = incantation_error;
        dprintf(cmd->client->socket_fd, KO);
    }
    command_t end = {"incantation_end", 300, func};
    new_command(server, cmd->client, end, cmd->cmd);
}
