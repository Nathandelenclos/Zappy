/*
** EPITECH PROJECT, 2023
**
** File description:
**
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "cmd.h"

    #define SIGN(x) (x < 0 ? -1 : 1)

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
void eject(server_t *server, cmd_t *cmd);

void mct(server_t *server, cmd_t *cmd);
void bct(server_t *server, cmd_t *cmd);
void tna(server_t *server, cmd_t *cmd);
void ppo(server_t *server, cmd_t *cmd);
void plv(server_t *server, cmd_t *cmd);
void pin(server_t *server, cmd_t *cmd);
void sgt(server_t *server, cmd_t *cmd);
void sst(server_t *server, cmd_t *cmd);

void eats(server_t *server, cmd_t *cmd);
void resource(server_t *server, cmd_t *cmd);

typedef struct {
    double x;
    double y;
} Point;

#endif /* !COMMANDS_H_ */
