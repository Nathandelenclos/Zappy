/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** game/commands/look.c
*/

#include "server.h"

/**
 * Get the tiles in the north direction.
 * @param server - The server.
 * @param cmd - The cmd.
 * @return
 */
node *look_north(server_t *server, cmd_t *cmd)
{
    map_t *map = cmd->client->player->map;
    node *tiles = NULL;
    put_in_end(&tiles, map->tile);
    for (int i = 1; i <= cmd->client->player->level; ++i) {
        map = map->up->left;
        map_t *line = map;
        put_in_end(&tiles, line->tile);
        for (int j = 0; j < i * 2; ++j) {
            line = line->right;
            put_in_end(&tiles, line->tile);
        }
    }
    return tiles;
}

/**
 * Get the tiles in the south direction.
 * @param server - The server.
 * @param cmd - The cmd.
 * @return
 */
node *look_south(server_t *server, cmd_t *cmd)
{
    map_t *map = cmd->client->player->map;
    node *tiles = NULL;
    put_in_end(&tiles, map->tile);
    for (int i = 1; i <= cmd->client->player->level; ++i) {
        map = map->down->left;
        map_t *line = map;
        put_in_end(&tiles, line->tile);
        for (int j = 0; j < i * 2; ++j) {
            line = line->right;
            put_in_end(&tiles, line->tile);
        }
    }
    return tiles;
}

/**
 * Get the tiles in the east direction.
 * @param server - The server.
 * @param cmd - The cmd.
 * @return
 */
node *look_east(server_t *server, cmd_t *cmd)
{
    map_t *map = cmd->client->player->map;
    node *tiles = NULL;
    put_in_end(&tiles, map->tile);
    for (int i = 1; i <= cmd->client->player->level; ++i) {
        map = map->up->right;
        map_t *line = map;
        put_in_end(&tiles, line->tile);
        for (int j = 0; j < i * 2; ++j) {
            line = line->down;
            put_in_end(&tiles, line->tile);
        }
    }
    return tiles;
}

/**
 * Get the tiles in the west direction.
 * @param server - The server.
 * @param cmd - The cmd.
 * @return
 */
node *look_west(server_t *server, cmd_t *cmd)
{
    map_t *map = cmd->client->player->map;
    node *tiles = NULL;
    put_in_end(&tiles, map->tile);
    for (int i = 1; i <= cmd->client->player->level; ++i) {
        map = map->down->left;
        map_t *line = map;
        put_in_end(&tiles, line->tile);
        for (int j = 0; j < i * 2; ++j) {
            line = line->up;
            put_in_end(&tiles, line->tile);
        }
    }
    return tiles;
}

/**
 * Print the tiles.
 * @param server - The server.
 * @param cmd - The cmd.
 * @param tiles - The tiles.
 */
void print_look(server_t *server, cmd_t *cmd, node *tiles)
{
    dprintf(cmd->client->socket_fd, "[");
    while (tiles) {
        tile_t *tile = tiles->data;
        node *items = tile->items;
        while (items) {
            item_t *item = items->data;
            dprintf(cmd->client->socket_fd, items->next == NULL ? "%s" : "%s ",
                item_type_str[item->type]);
            items = items->next;
        }
        if (tiles->next) {
            dprintf(cmd->client->socket_fd, ", ");
        }
        tiles = tiles->next;
    }
    dprintf(cmd->client->socket_fd, "]\n");
}

/**
 * Look north.
 * @param server - The server.
 * @param cmd - The cmd.
 */
void look(server_t *server, cmd_t *cmd)
{
    client_t *client = cmd->client;
    int dir = client->player->direction;
    node *tiles = NULL;
    if (dir == NORTH) {
        tiles = look_north(server, cmd);
    }
    if (dir == SOUTH) {
        tiles = look_south(server, cmd);
    }
    if (dir == EAST) {
        tiles = look_east(server, cmd);
    }
    if (dir == WEST) {
        tiles = look_west(server, cmd);
    }
    print_look(server, cmd, tiles);
}
