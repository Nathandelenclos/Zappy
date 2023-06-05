/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** network/handle_client.c
*/

#include <stdbool.h>
#include "server.h"

void handle_client(server_t *server)
{
    int activity;
    server->last_fd = server->socket_fd;
    bool is_running = true;
    while (is_running) {
        FD_ZERO(&server->readfds);
        FD_SET(0, &server->readfds);
        FD_SET(server->socket_fd, &server->readfds);
        for (node *tmp = server->clients;
            tmp != NULL; tmp = tmp->next)
            FD_SET(((client_t *) tmp->data)->socket_fd, &server->readfds);
            activity = select(server->last_fd + 1, &server->readfds, NULL, NULL,
            NULL);
        if ((activity < 0) && (errno != EINTR)) {
            printf("Erreur lors de la surveillance des sockets\n");
        }
        new_connection(server);
    }
}
