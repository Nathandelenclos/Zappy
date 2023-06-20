/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** message.h
*/

#include "server.h"

/**
 *
 * @param server
 * @param cmd
 */
void eats(server_t *server, cmd_t *cmd)
{
    if (get_item_count(cmd->client->player->inventory, FOOD) == 0) {
        dprintf(cmd->client->socket_fd, DEAD);
        return;
    }
    remove_item_from_inventory(&cmd->client->player->inventory, FOOD);
    command_t command = {NULL, 126, eats};
    new_command(server, cmd->client, command, "eat");
}
