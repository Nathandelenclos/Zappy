/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** game/commands/broadcast.c
*/

#include "server.h"

double crossProduct(Point v1, Point v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

int isPointInAngle(Point A1, Point A2, Point side1, Point side2) {
    Point vector1 = { side1.x - A1.x, side1.y - A1.y };
    Point vector2 = { side2.x - A1.x, side2.y - A1.y };
    Point pointVector = { A2.x - A1.x, A2.y - A1.y };

    double cross1 = crossProduct(vector1, pointVector);
    double cross2 = crossProduct(pointVector, vector2);

    if (cross1 >= 0 && cross2 >= 0) {
        return 1; // A2 est dans la zone de l'angle
    } else {
        return 0; // A2 est en dehors de la zone de l'angle
    }
}

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

void broadcast(server_t *server, cmd_t *cmd)
{
    client_t *client = cmd->client;
    node *client_ai = get_all_ia_client(server);
    for (node *tmp = client_ai; tmp; tmp = tmp->next) {
        client_t *client_tmp = tmp->data;
        if (client_tmp == client) {
            continue;
        }
        Point A1 = { ((double)client_tmp->player->map->pos_x), ((double)client_tmp->player->map->pos_y)};
        Point A2 = { ((double)client->player->map->pos_x), ((double)client->player->map->pos_y)};

        if (A1.x == A2.x && A1.y == A2.y) {
            dprintf(client_tmp->socket_fd, "0\n");
            continue;
        }
        bool isInAngles = false;
        for (int i = 0; i < 8; ++i) {
            int isInAngle = isPointInAngle(A1, A2, pair_angle_broadcast[i][0], pair_angle_broadcast[i][1]);
            int res =  ((1 + ((int)client_tmp->player->direction) * 2) + i) % 8;

            if (isInAngle) {
                dprintf(client_tmp->socket_fd, "%d\n", res == 0 ? 8 : res);
                isInAngles = true;
                break;
            }

        }
        dprintf(client_tmp->socket_fd, "%s\n", isInAngles ? "True" : "False");
    }
}
