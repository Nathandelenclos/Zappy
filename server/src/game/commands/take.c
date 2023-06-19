/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** game/commands/right.c
*/

#include "server.h"

/**
 * Add item to inventory.
 * @param inventory - The inventory.
 * @param item_type - The item type.
 */
void add_item_to_inventory(node **inventory, item_type_t item_type)
{
    item_t *item = MALLOC(sizeof(item_t));
    item->type = item_type;
    put_in_list(inventory, item);
}

/**
 * Get item count.
 * @param inventory - The inventory.
 * @param item_type - The item type.
 * @return int - The item count.
 */
void remove_item_from_inventory(node *inventory, item_type_t item_type)
{
    node *tmp = inventory;
    item_t *item = NULL;

    while (tmp != NULL) {
        item = tmp->data;
        if (item->type == item_type) {
            delete_in_list(&inventory, item);
            return;
        }
        tmp = tmp->next;
    }
}

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
                remove_item_from_inventory(cmd->client->player->map->tile->items, i);
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
