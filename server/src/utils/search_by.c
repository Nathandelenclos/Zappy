/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** utils/search_by_string.c
*/

#include <string.h>
#include <server.h>

/**
 * Search by string.
 * @param data - The data.
 * @param arg - The arg.
 * @return - Return true if data == arg.
 */
int search_by_string(void * data, void *arg)
{
    return strcmp((string)data, (string)arg);
}


int search_by_team(void *data, void *arg)
{
    return strcmp(((team_t *)data)->name, (string)arg);
}

int search_by_player(void *data, void *arg)
{
    client_t *client = (client_t *)data;
    player_t *player = (player_t *)arg;
    if (client->player == player)
        return 0;
    return 1;
}
