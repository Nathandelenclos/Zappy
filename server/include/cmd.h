/*
** EPITECH PROJECT, 2023
** server
** File description:
** cmd.h
*/

#ifndef SERVER_CMD_H
    #define SERVER_CMD_H

    #include "my.h"
    #include "list.h"

typedef unsigned long long timestamp_t;
typedef struct client_s client_t;
typedef struct server_s server_t;

typedef enum {
    NOT_STARTED,
    STARTED,
    FINISHED
} STATE_CMD;

typedef struct cmd_s {
    timestamp_t timestamp_start;
    timestamp_t timestamp_end;
    client_t *client;
    string cmd;
    STATE_CMD state;
    void (*func)(server_t *server, struct cmd_s *cmd);
} cmd_t;

typedef struct list_s cmd_queue_t;

cmd_t *create_cmd(client_t *client_socket, string cmd, timestamp_t timestamp_start,
    timestamp_t timestamp_end, void (*func)(server_t *server, cmd_t *cmd));
void add_cmd(cmd_t *cmd, cmd_queue_t **queue);
cmd_queue_t *pop_first(cmd_queue_t **queue);

#endif //SERVER_CMD_H
