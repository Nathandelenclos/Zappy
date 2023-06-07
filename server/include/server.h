/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** server.h
*/

#ifndef SERVER_H_
    #define SERVER_H_

#include <stdbool.h>
#include "my.h"
    #include "list.h"
    #include "network.h"
    #include "map.h"
    #include "player.h"
    #include "utils.h"

    #define MAX_CONNECTIONS 1024

typedef enum {
    WAITING_TEAM_NAME,
    WAITING_COMMAND,
} STATE_CONNECTION;

typedef struct {
    int socket_fd;
    struct sockaddr_in sockaddr;
    socklen_t len;
    player_t *player;
    STATE_CONNECTION state;
} client_t;

typedef struct {
    args_t *args;
    int socket_fd;
    struct sockaddr_in sockaddr;
    fd_set readfds;
    int last_fd;
    bool is_running;
    node *clients;
    node *commands;
} server_t;

server_t *create_server(args_t *args);
void handle_client(server_t *server);
void new_connection(server_t *server);
client_t *create_client(server_t *server);
void action(server_t *server);

#endif /* !SERVER_H_ */
