/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** map/generate.c
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
 * Add items to inventory.
 * @param inventory - The inventory.
 * @param item_type - The item type.
 * @param quantity - The quantity.
 */
void add_items_to_inventory(node **inventory, item_type_t item_type, int quantity)
{
    for (int i = 0; i < quantity; ++i) {
        add_item_to_inventory(inventory, item_type);
    }
}

/**
 * Get item count.
 * @param inventory - The inventory.
 * @param item_type - The item type.
 * @return int - The item count.
 */
bool remove_item_from_inventory(node **inventory, item_type_t item_type)
{
    node *tmp = *inventory;
    item_t *item = NULL;

    while (tmp != NULL) {
        item = tmp->data;
        if (item->type == item_type) {
            return delete_in_list(inventory, item);
        }
        tmp = tmp->next;
    }
    return false;
}
