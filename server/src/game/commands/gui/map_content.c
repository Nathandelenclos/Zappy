/*
** EPITECH PROJECT, 2023
** server
** File description:
** map_content.c
*/
#include "server.h"

/**
 * Get the map size.
 * @param server - The server.
 * @param cmd - The command.
 */
void msz(server_t *server, cmd_t *cmd)
{
    dprintf(cmd->client->socket_fd, "msz %d %d\n",
            server->args->width, server->args->height);
}

/**
 * Get the whole map content.
 * @param server - The server.
 * @param cmd - The command.
 */
void mct(server_t *server, cmd_t *cmd)
{
    map_t *map = server->map;
    char buffer[10000] = {0};
    int offset = 0;

    for (int y = 0; y < server->args->height; y++) {
        for (int x = 0; x < server->args->width; x++) {
            offset += snprintf(buffer + offset, sizeof(buffer) - offset,
                               "bct %d %d %d %d %d %d %d %d %d\n",
                               x, y,
                               get_item_count(map->tile->items, FOOD),
                               get_item_count(map->tile->items, LINEMATE),
                               get_item_count(map->tile->items, DERAUMERE),
                               get_item_count(map->tile->items, SIBUR),
                               get_item_count(map->tile->items, MENDIANE),
                               get_item_count(map->tile->items, PHIRAS),
                               get_item_count(map->tile->items, THYSTAME));
            map = map->right;
        }
        map = map->down;
    }
    write(cmd->client->socket_fd, buffer, offset);
}

/**
 * Get the content of a tile.
 * @param server - The server.
 * @param cmd - The command.
 */
void bct(server_t *server, cmd_t *cmd)
{
    map_t *map = server->map;
    parse_cmd_arg(cmd->cmd, true);
    int x = parse_cmd_arg(cmd->cmd, false);
    int y = parse_cmd_arg(cmd->cmd, false);

    if (x < 0 || x >= server->args->width || y < 0 || y >= server->args->height) {
        dprintf(cmd->client->socket_fd, "sbp\n");
        return;
    }
    for (int i = 0; i < y; i++)
        map = map->down;
    for (int i = 0; i < x; i++)
        map = map->right;
    dprintf(cmd->client->socket_fd, "bct %d %d %d %d %d %d %d %d %d\n",
            x, y,
            get_item_count(map->tile->items, FOOD),
            get_item_count(map->tile->items, LINEMATE),
            get_item_count(map->tile->items, DERAUMERE),
            get_item_count(map->tile->items, SIBUR),
            get_item_count(map->tile->items, MENDIANE),
            get_item_count(map->tile->items, PHIRAS),
            get_item_count(map->tile->items, THYSTAME));
}