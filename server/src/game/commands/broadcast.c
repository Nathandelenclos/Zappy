/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** game/commands/broadcast.c
*/

#include "server.h"
#include "math.h"

/**
 * Get IA client.
 * @param server -
 * @return
 */
node *get_all_ia_client(server_t *server)
{
    node *tmp = server->clients;
    node *ia_clients = NULL;

    while (tmp) {
        if (((client_t *)tmp->data)->type == AI)
            put_in_list(&ia_clients, tmp->data);
        tmp = tmp->next;
    }
    return ia_clients;
}

/**
 *
 * @param client
 * @param cell
 * @return
 */
int to_direction(client_t *client, int cell)
{
    if (cell == 0)
        return 0;
    if (client->player->direction == NORTH)
        cell -= 2;
    if (client->player->direction == SOUTH)
        cell -= 6;
    if (client->player->direction == WEST)
        cell -= 4;
    cell += cell < 1 ? 8 : 0;
    return cell;
}

void broadcast(server_t *server, cmd_t *cmd)
{
    client_t *client = cmd->client;
    node *client_ai = get_all_ia_client(server);
    for (node *tmp = client_ai; tmp; tmp = tmp->next) {
        client_t *client_tmp = tmp->data;
        if (client_tmp == client)
            continue;
        Point A1 = { ((double)client_tmp->player->map->pos_x), ((double)client_tmp->player->map->pos_y)};
        Point A2 = { ((double)client->player->map->pos_x), ((double)client->player->map->pos_y)};
        Point B1 = { A2.x - A1.x, (-A2.y) - (-A1.y) };
        if (B1.x == 0 && B1.y == 0) {
            dprintf(client_tmp->socket_fd, "message 0, %s\n", strlen(cmd->cmd) <= 10 ? "" : cmd->cmd + 10);
            continue;
        }
        B1.x -= abs(B1.x) > server->args->width / 2 ? server->args->width * SIGN(B1.x) : 0;
        B1.y -= abs(B1.y) > server->args->height / 2 ? server->args->height * SIGN(B1.y) : 0;
        double angle = atan2(B1.y, B1.x) * 180 / M_PI;
        angle = angle < 0 ? angle + 360 : angle;
        int cell = (int)(round(fmod((((angle - fmod(angle, 22.5)) / 22.5) / 2), 8)) + 1);
        dprintf(client_tmp->socket_fd, "message %d, %s\n",
            to_direction(client_tmp, cell), strlen(cmd->cmd) <= 10 ? "" : cmd->cmd + 10);
    }
    dprintf(server->gui->socket_fd, "pbc %d %s\n", client->socket_fd,
            strlen(cmd->cmd) <= 10 ? "" : cmd->cmd + 10);
}
