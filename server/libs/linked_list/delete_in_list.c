/*
** EPITECH PROJECT, 2021
** LINKED LIST
** File description:
** delete in list
*/

#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * Delete a node in the list.
 * @param head_ref - Head of the list.
 * @param key - Data to delete.
 */
bool delete_in_list(node **head_ref, void *key)
{
    node *temp = *head_ref, *prev;
    if (temp != NULL && temp->data == key) {
        *head_ref = temp->next;
        FREE(temp);
        return true;
    }

    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return false;
    }
    prev->next = temp->next;
    FREE(temp);
    return true;
}
