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
    string have_return = strstr(buffer, "\n");
    string have_return2 = strstr(buffer, "\r");
    if (have_return != NULL) {
        have_return[0] = '\0';
    }
    if (have_return2 != NULL) {
        have_return2[0] = '\0';
    }
    return my_strdup(buffer);
}
