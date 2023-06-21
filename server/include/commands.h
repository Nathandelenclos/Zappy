/*
** EPITECH PROJECT, 2023
**
** File description:
**
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "cmd.h"

typedef struct server_s server_t;
typedef struct client_s client_t;
typedef char *string;

void debug_cmd(server_t *server, cmd_t *cmd);
void forward(server_t *server, cmd_t *cmd);
void right(server_t *server, cmd_t *cmd);
void left(server_t *server, cmd_t *cmd);
void look(server_t *server, cmd_t *cmd);
void inventory(server_t *server, cmd_t *cmd);
void take(server_t *server, cmd_t *cmd);
void set(server_t *server, cmd_t *cmd);
void incantation(server_t *server, cmd_t *cmd);
void incantation_start(server_t *server, cmd_t *cmd);
void connect_nbr(server_t *server, cmd_t *cmd);
void fork_cmd(server_t *server, cmd_t *cmd);
void broadcast(server_t *server, cmd_t *cmd);
void msz(server_t *server, cmd_t *cmd);
void mct(server_t *server, cmd_t *cmd);
void bct(server_t *server, cmd_t *cmd);
void tna(server_t *server, cmd_t *cmd);
void ppo(server_t *server, cmd_t *cmd);
void plv(server_t *server, cmd_t *cmd);
void pin(server_t *server, cmd_t *cmd);
void sgt(server_t *server, cmd_t *cmd);
void sst(server_t *server, cmd_t *cmd);

typedef struct {
    double x;
    double y;
} Point;

static const Point pair_angle_broadcast[8][2] = {
    {
        {1, 0},
        {2 , 0},
    },
    {
        {2, 0},
        {3, 1},
    },
    {
        {3, 1},
        {3, 2},
    },
    {
        {3, 2},
        {2, 3},
    },
    {
        {2, 3},
        {1, 3},
    },
    {
        {1, 3},
        {0, 2},
    },
    {
        {0, 2},
        {0, 1},
    },
    {
        {0, 1},
        {1, 0},
    }
};

#endif /* !COMMANDS_H_ */
