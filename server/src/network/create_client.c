/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** network/create_client.c
*/

#include "server.h"

/**
 * Create a client.
 * @param server - The server.
 * @return The client.
 */
client_t *create_client(server_t *server)
{
    client_t *client = MALLOC(sizeof(client_t));
    if (!client) {
        return NULL;
    }
    struct sockaddr_in address;
    client->len = sizeof(address);
    client->socket_fd = accept(server->socket_fd,
        (struct sockaddr *)
            &address,
        &client->len);
    client->sockaddr = address;
    client->state = WAITING_TEAM_NAME;
    client->commands = NULL;
}
