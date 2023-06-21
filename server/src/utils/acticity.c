/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** network/actions.c
*/

#include "server.h"

/**
 * Pause current activity.
 * @param server - The server.
 * @param clients - The clients.
 */
void pause_activity(server_t *server, node *clients)
{
    client_t *client;
    for (node *tmp = clients; tmp; tmp = tmp->next) {
        client = tmp->data;
        cmd_t *last_command = client->commands->data;
        if (last_command->state == STARTED) {
            last_command->state = PAUSE;
            last_command->timestamp_end = server->time;
            delete_in_list(&server->cmd_queue, last_command);
        }
    }
}

/**
 * Resume current activity.
 * @param server - The server.
 * @param clients - The clients.
 */
void resume_activity(server_t *server, node *clients)
{
    client_t *client;
    for (node *tmp = clients; tmp; tmp = tmp->next) {
        client = tmp->data;
        cmd_t *cmd_tmp;
        for (node *node_cmd = client->commands; node_cmd; node_cmd = node_cmd->next) {
            cmd_tmp = node_cmd->data;
            if (cmd_tmp->state == PAUSE) {
                cmd_tmp->state = STARTED;
                timestamp_t diff =
                    cmd_tmp->timestamp_end - cmd_tmp->timestamp_start;
                timestamp_t need_time = (cmd_tmp->ticks != 0 ?
                    (((cmd_tmp->ticks * 1000) / server->args->freq)) : 0);
                cmd_tmp->timestamp_end = server->time + (need_time - diff);
                add_cmd(cmd_tmp, &server->cmd_queue);
                break;
            }
        }
    }
}
