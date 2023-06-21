/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** game/commands/inventory.c
*/

#include "server.h"

/**
 * Get the number of items in the inventory.
 * @param inventory - The inventory.
 * @param type - The type of the item.
 * @return
 */
int get_item_count(node *inventory, item_type_t type)
{
    int count = 0;
    node *tmp = inventory;

    while (tmp) {
        if (((item_t *)tmp->data)->type == type)
            count++;
        tmp = tmp->next;
    }
    return count;
}

/**
 * Inventory cmd.
 * @param server - The server.
 * @param cmd - The cmd.
 */
void inventory(server_t *server, cmd_t *cmd)
{
    dprintf(cmd->client->socket_fd, "[");
    for (int i = 1; item_type_str[i] != NULL; ++i) {
        dprintf(cmd->client->socket_fd, item_type_str[i + 1] == NULL ? "%s %d" : "%s %d, ", item_type_str[i],
            get_item_count(cmd->client->player->inventory, i));
    }
    dprintf(cmd->client->socket_fd, "]\n");
}
