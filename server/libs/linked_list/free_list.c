/*
** EPITECH PROJECT, 2021
** LINKED_LIST
** File description:
** free_list
*/

#include "list.h"
#include <stdlib.h>

/**
 * Free the list.
 * @param head - Head of the list.
 * @param p_free - Function to free the data.
 * @return 0 if success, -1 if error.
 */
int free_list(node *head, void (*p_free)(void *data))
{
    node* tmp;

    while (head != NULL) {
        tmp = head;
        head = head->next;
        if (tmp->data != NULL)
            p_free(tmp->data);
        free(tmp);
    }
    return (0);
}
