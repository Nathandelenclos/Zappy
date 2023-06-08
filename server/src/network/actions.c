/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** network/actions.c
*/

#include "server.h"

string read_message(client_t *client)
{
    char buffer[1024] = {0};
    int valread = read(client->socket_fd, buffer, 1024);
    if (valread == 0) {
        return NULL;
    }
    return my_strdup(buffer);
}

void action(server_t *server, client_t *client)
{
    string action = read_message(client);
    if (action == NULL)
        return;

    FREE(action);
}

/**
 * Handle client.
 * @param server - The server.
 */
void handle_action(server_t *server)
{
    if (!(server->is_running))
        return;
    for (node *tmp = server->clients; tmp != NULL; tmp = tmp->next) {
        client_t *client = (client_t *) tmp->data;
        if (FD_ISSET(client->socket_fd, &server->readfds))
            action(server, client);
    }
}
