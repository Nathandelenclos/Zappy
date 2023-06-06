/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** network/actions.c
*/

#include "server.h"

/**
 * Handle client.
 * @param server - The server.
 */
void action(server_t *server)
{
    if (!(server->is_running))
        return;
    for (node *tmp = server->clients; tmp != NULL; tmp = tmp->next) {
        client_t *client = (client_t *) tmp->data;
        if (FD_ISSET(client->socket_fd, &server->readfds)) {
            packet_t *socket = read_packet(client->socket_fd);
            //TODO: Handle packet
            FREE(socket);
        }
    }
}
