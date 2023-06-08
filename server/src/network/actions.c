/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** network/actions.c
*/

#include "server.h"

/**
 * Read message.
 * @param client - The client.
 * @return The message.
 */
string read_message(client_t *client)
{
    char buffer[1024] = {0};
    int valread = read(client->socket_fd, buffer, 1024);
    if (valread == 0) {
        return NULL;
    }
    return my_strdup(buffer);
}

/**
 * Handle action.
 * @param server - The server.
 * @param client - The client.
 */
void action(server_t *server, client_t *client)
{
    string action = read_message(client);
    if (action == NULL)
        return;
    if (client->state == WAITING_TEAM_NAME) {
        client->team = search_in_list_by(server->teams, action,
            search_by_string)->data;
        if (client->team == NULL) {
            dprintf(client->socket_fd, KO);
            return;
        }
        client->state = WAITING_COMMAND;
    } else if (client->state == WAITING_COMMAND) {
        // TODO: Handle command
    }
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
