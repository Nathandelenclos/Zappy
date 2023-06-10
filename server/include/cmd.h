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
    #include "server.h"

typedef enum {
    NOT_STARTED,
    STARTED,
    FINISHED
} STATE_CMD;

typedef struct {
    unsigned int timestamp_start;
    unsigned int timestamp_end;
    client_t *client_socket;
    STATE_CMD state;
} cmd_t;

typedef struct list_s cmd_queue_t;

cmd_t *create_cmd(client_t *client_socket, unsigned int timestamp_start,
                  unsigned int timestamp_end, void *cmd);
void add_cmd(cmd_t *cmd, cmd_queue_t **queue);

#endif //SERVER_CMD_H
