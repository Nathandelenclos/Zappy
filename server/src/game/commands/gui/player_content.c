/*
** EPITECH PROJECT, 2023
** server
** File description:
** player_content.c
*/
#include "server.h"

static void print_err_arg(cmd_t *cmd)
{
    dprintf(cmd->client->socket_fd, "sbp\n");
}

static node *parse_and_find_client_by_id(server_t *server, cmd_t *cmd)
{
    client_t *tmp = NULL;
    node *client = server->clients;

    parse_cmd_arg(cmd->cmd, true);
    int id = parse_cmd_arg(cmd->cmd, false);
    if (id == -1) {
        return NULL;
    }
    while (client != NULL) {
        tmp = (client_t *)client->data;
        if (tmp->socket_fd == id)
            return client;
        client = client->next;
    }
    return NULL;
}

/**
 * Get a player's position
 * @param server - The server.
 * @param cmd - The cmd.
 */
void ppo(server_t *server, cmd_t *cmd)
{
    node *client = parse_and_find_client_by_id(server, cmd);
    client_t *tmp = NULL;

    if (client == NULL)
        return print_err_arg(cmd);
    tmp  = (client_t *)client->data;
    if (strcmp(tmp->team->name, GRAPHIC) == 0) {
        return print_err_arg(cmd);
    }
    dprintf(cmd->client->socket_fd, "ppo %d %d %d %d\n", tmp->socket_fd,
        tmp->player->map->pos_x, tmp->player->map->pos_y, tmp->player->direction);
}

/**
 * Get a player's level
 * @param server - The server.
 * @param cmd - The cmd.
 */
void plv(server_t *server, cmd_t *cmd)
{
    node *client = parse_and_find_client_by_id(server, cmd);
    client_t *tmp = NULL;

    if (client == NULL)
        return print_err_arg(cmd);
    tmp  = (client_t *)client->data;
    if (strcmp(tmp->team->name, GRAPHIC) == 0) {
        return print_err_arg(cmd);
    }
    dprintf(cmd->client->socket_fd, "plv %d %d\n", tmp->socket_fd,
        tmp->player->level);
}

/**
 * Get a player's inventory
 * @param server - The server.
 * @param cmd - The cmd.
 */
void pin(server_t *server, cmd_t *cmd)
{
    node *client = parse_and_find_client_by_id(server, cmd);
    client_t *tmp = NULL;

    if (client == NULL)
        return print_err_arg(cmd);
    tmp  = (client_t *)client->data;
    if (strcmp(tmp->team->name, GRAPHIC) == 0) {
        return print_err_arg(cmd);
    }
    dprintf(cmd->client->socket_fd, "pin %d %d %d %d %d %d %d %d %d %d\n",
        tmp->socket_fd, tmp->player->map->pos_x, tmp->player->map->pos_y,
            get_item_count(tmp->player->inventory,FOOD),
            get_item_count(tmp->player->inventory,LINEMATE),
            get_item_count(tmp->player->inventory, DERAUMERE),
        get_item_count(tmp->player->inventory, SIBUR),
        get_item_count(tmp->player->inventory, MENDIANE),
        get_item_count(tmp->player->inventory,PHIRAS),
        get_item_count(tmp->player->inventory, THYSTAME));
}
