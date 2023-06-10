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

    if (((cmd_t*)tmp->data)->timestamp_start >
    ((cmd_t*)new_node->data)->timestamp_start) {
        new_node->next = tmp;
        *queue = new_node;
        return;
    }
    while (tmp->next != NULL &&
    ((cmd_t*)tmp->data)->timestamp_start <
    ((cmd_t*)new_node->data)->timestamp_start) {
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
    if (*queue == NULL) {
        *queue = new_node;
        return;
    }
    add_sorted(new_node, queue);
}

/**
 * Create a command.
 * @param client_socket
 * @param timestamp_start
 * @param timestamp_end
 * @param cmd
 * @return Command.
 */
cmd_t *create_cmd(client_t *client_socket, unsigned int timestamp_start,
    unsigned int timestamp_end, void *cmd)
    // TODO: Change void *cmd to its real type
{
    cmd_t *new_cmd = MALLOC(sizeof(cmd_t));

    new_cmd->client_socket = client_socket;
    new_cmd->timestamp_start = timestamp_start;
    new_cmd->timestamp_end = timestamp_end;
    new_cmd->state = NOT_STARTED;
    return (new_cmd);
}