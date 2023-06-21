/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** network/new_connection.c
*/

#include "server.h"

/**
 * Handle new connection.
 * @param server - The server.
 */
void new_connection(server_t *server)
{
    if (FD_ISSET(server->socket_fd, &server->readfds)) {
        client_t *client = create_client(server);
        if (client->socket_fd < 0) {
            perror_exit(ERROR_CONNEXION);
        }
        server->last_fd = client->socket_fd;
        put_in_list(&server->clients, client);
        dprintf(client->socket_fd, WELCOME);
    }
}
