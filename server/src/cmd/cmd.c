/*
** EPITECH PROJECT, 2023
** server
** File description:
** cmd.c
*/
#include "cmd.h"

/**
 * Add a command to the queue sorted by timestamp.
 * @param new_node - Command to add.
 * @param queue - Queue to add the command to.
 */
static void add_sorted(node *new_node, cmd_queue_t **queue)
{
    node *tmp = *queue;

    if (((cmd_t*)tmp->data)->timestamp_end >
    ((cmd_t*)new_node->data)->timestamp_end) {
        new_node->next = tmp;
        *queue = new_node;
        return;
    }
    while (tmp->next != NULL &&
    ((cmd_t*)tmp->data)->timestamp_end <
    ((cmd_t*)new_node->data)->timestamp_end) {
        tmp = tmp->next;
    }
    new_node->next = tmp->next;
    tmp->next = new_node;
}

/**
 * Add a command to the queue sorted by timestamp.
 * @param cmd - Command.
 * @param queue - Address of the queue to add the command to.
 */
void add_cmd(cmd_t *cmd, cmd_queue_t **queue)
{
    node *new_node = MALLOC(sizeof(node));

    new_node->data = cmd;
    new_node->next = NULL;

    if (*queue == NULL || cmd->timestamp_end < ((cmd_t *)(*queue)->data)->timestamp_end) {
        new_node->next = *queue;
        *queue = new_node;
    } else {
        node *current = *queue;
        while (current->next != NULL &&
        ((cmd_t*)current->next->data)->timestamp_end <
        ((cmd_t*)new_node->data)->timestamp_end) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

/**
 * Create a command.
 * @param client_socket
 * @param timestamp_start
 * @param timestamp_end
 * @param cmd
 * @return Command.
 */
cmd_t *create_cmd(client_t *client_socket, string cmd, timestamp_t timestamp_start,
    timestamp_t timestamp_end, void (*func)(server_t *server, cmd_t *cmd))
{
    cmd_t *new_cmd = MALLOC(sizeof(cmd_t));

    new_cmd->client = client_socket;
    new_cmd->timestamp_start = timestamp_start;
    new_cmd->timestamp_end = timestamp_end;
    new_cmd->func = func;
    new_cmd->cmd = cmd;
    new_cmd->state = STARTED;
    return (new_cmd);
}

/**
 * Pop the first command of the queue.
 * @param queue - Queue to pop the command from.
 * @return The popped command.
 */
cmd_queue_t *pop_first(cmd_queue_t **queue)
{
    cmd_queue_t *tmp = queue;

    if (queue == NULL)
        return NULL;
    *queue = (*queue)->next;
    return tmp;
}
