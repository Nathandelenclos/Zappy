/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** network/actions.c
*/

#include "server.h"

/**
 * Handle action.
 * @param server - The server.
 * @param client - The client.
 */
void new_graphic_client(server_t *server, client_t *client)
{
    char buffer[10000] = {0};
    int offset = 0;
    map_t *map = server->map;
    client->team = search_in_list_by(server->teams, "GRAPHIC",
                                     search_by_team)->data;
    client->type = GUI;
    client->state = WAITING_COMMAND;
    server->gui = client;
    offset += snprintf(buffer + offset, sizeof(buffer) - offset,
                       "msz %d %d\nsgt %d\n", server->args->width,
                       server->args->height, server->args->freq);
    for (int y = 0; y < server->args->height; y++) {
        for (int x = 0; x < server->args->width; x++) {
            offset += snprintf(buffer + offset, sizeof(buffer) - offset,
                               "bct %d %d %d %d %d %d %d %d %d\n",
                               x, y,
                               get_item_count(map->tile->items, FOOD),
                               get_item_count(map->tile->items, LINEMATE),
                               get_item_count(map->tile->items, DERAUMERE),
                               get_item_count(map->tile->items, SIBUR),
                               get_item_count(map->tile->items, MENDIANE),
                               get_item_count(map->tile->items, PHIRAS),
                               get_item_count(map->tile->items, THYSTAME));
            map = map->right;
        }
        map = map->down;
    }
    for (node *teams = server->teams; teams; teams = teams->next) {
        team_t *team = teams->data;
        if (strcmp(team->name, "GRAPHIC") == 0)
            continue;
        offset += snprintf(buffer + offset, sizeof(buffer) - offset,
                           "tna %s\n", team->name);
    }
    write(client->socket_fd, buffer, offset);
}

/**
 * New ai client.
 * @param server - The server.
 * @param client - The client.
 * @param action - The action.
 */
void new_ai_client(server_t *server, client_t *client, string action)
{
    client->type = AI;
    node *team = search_in_list_by(server->teams, action, search_by_team);
    if (team == NULL) {
        dprintf(client->socket_fd, KO);
        return;
    }
    client->team = team->data;
    if (len_list(client->team->eggs_places) <= 0) {
        dprintf(client->socket_fd, KO);
        return;
    }
    client->state = WAITING_COMMAND;
    new_player(server, client);
    dprintf(client->socket_fd, "%d\n%d %d\n", server->args->clients_nb,
        server->args->width, server->args->height);
}

/**
 * Handle action.
 * @param server - The server.
 * @param client - The client.
 */
void action(server_t *server, client_t *client)
{
    string action = read_message(client);
    if (action == NULL) {
        if (client->type == AI && client->player != NULL) {
            put_in_list(&client->team->eggs_places, client->player->map);
            add_item_to_inventory(&client->player->map->tile->items, EGG);
            delete_in_list(&client->player->map->tile->items, client);
            delete_in_list(&server->clients, client);
        }
        return;
    }
    if (client->state == WAITING_TEAM_NAME) {
        if (strcmp(action, GRAPHIC) == 0) {
            new_graphic_client(server, client);
            return;
        }
        new_ai_client(server, client, action);
    } else if (client->state == WAITING_COMMAND) {
        find_command(server, client, action);
    }
    FREE(action);
}

/**
 * Handle client.
 * @param server - The server.
 */
void handle_action(server_t *server)
{
    if (!(server->is_running)) {
        return;
    }
    for (node *tmp = server->clients; tmp != NULL; tmp = tmp->next) {
        client_t *client = (client_t *) tmp->data;
        if (FD_ISSET(client->socket_fd, &server->readfds)) {
            action(server, client);
            return;
        }
    }
}
