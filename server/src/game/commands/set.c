/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** game/commands/right.c
*/

#include "server.h"

/**
 * Set cmd.
 * @param server - The server.
 * @param cmd - The cmd.
 */
void set(server_t *server, cmd_t *cmd)
{
    for (int i = 1; item_type_str[i] != NULL; ++i) {
        if (strstr(cmd->cmd, item_type_str[i])) {
            if (get_item_count(cmd->client->player->inventory, i) > 0) {
                add_item_to_inventory(&cmd->client->player->map->tile->items, i);
                remove_item_from_inventory(&cmd->client->player->inventory, i);
                dprintf(cmd->client->socket_fd, "ok\n");
                return;
            } else {
                dprintf(cmd->client->socket_fd, "ko\n");
                return;
            }
        }
    }
    dprintf(cmd->client->socket_fd, "ko\n");
}
