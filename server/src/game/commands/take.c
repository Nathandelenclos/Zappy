/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** game/commands/take.c
*/

#include "server.h"

/**
 * Take cmd.
 * @param server - The server.
 * @param cmd - The cmd.
 */
void take(server_t *server, cmd_t *cmd)
{
    for (int i = 1; item_type_str[i] != NULL; ++i) {
        if (strstr(cmd->cmd, item_type_str[i])) {
            if (get_item_count(cmd->client->player->map->tile->items, i) > 0) {
                add_item_to_inventory(&cmd->client->player->inventory, i);
                remove_item_from_inventory(
                    &cmd->client->player->map->tile->items, i);
                if (server->gui != NULL)
                    dprintf(server->gui->socket_fd, "pgt %d %d\n",
                        cmd->client->socket_fd, i);
                dprintf(cmd->client->socket_fd, OK);
                return;
            } else {
                dprintf(cmd->client->socket_fd, KO);
                return;
            }
        }
    }
    dprintf(cmd->client->socket_fd, KO);
}
