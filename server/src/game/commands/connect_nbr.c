/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** game/commands/forward.c
*/

#include "server.h"

void connect_nbr(server_t *server, cmd_t *cmd)
{
    dprintf(cmd->client->socket_fd, "%d\n", len_list(cmd->client->team->eggs_places));
}
