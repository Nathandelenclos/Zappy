/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** network/handle_client.c
*/

#include "server.h"

/**
 * Update state of command in commands of client.
 * @param client - The client.
 */
void update_state(client_t *client)
{
    cmd_t *last = NULL;
    for (node *tmp = client->commands; tmp; tmp = tmp->next) {
        last = tmp->data;
        if (tmp->next == NULL)
            break;
        if (last->state == NOT_STARTED && ((cmd_t *)tmp->next->data)->state == FINISHED ) {
            last->state = STARTED;
        }
    }
}

/**
 * Exec queue.
 * @param server - The server.
 */
void exec_queue(server_t *server)
{
    if (server->cmd_queue == NULL)
        return;
    cmd_t *cmd = server->cmd_queue->data;
    while (cmd->timestamp_end <= server->time) {
        if (cmd->client->player->alive)
            cmd->func(server, cmd);
        cmd->state = FINISHED;
        update_state(cmd->client);
        server->cmd_queue = server->cmd_queue->next;
        if (server->cmd_queue == NULL)
            return;
        cmd = server->cmd_queue->data;
    }
}

/**
 * Handle action.
 * @param server - The server.
 */
void handle_client(server_t *server)
{
    int activity;
    server->last_fd = server->socket_fd;
    struct timeval timeval  = {0 , 0};
    while (server->is_running) {
        timeval.tv_usec = 1000;
        exec_queue(server);
        FD_ZERO(&server->readfds);
        FD_SET(server->socket_fd, &server->readfds);
        for (node *tmp = server->clients; tmp != NULL; tmp = tmp->next)
            FD_SET(((client_t *) tmp->data)->socket_fd, &server->readfds);
        activity = select(server->last_fd + 1, &server->readfds, NULL, NULL, &timeval);
        server->time++;
        if ((activity < 0) && (errno != EINTR)) {
            printf(ERROR_SOCKET);
        }
        handle_action(server);
        new_connection(server);
    }
}
