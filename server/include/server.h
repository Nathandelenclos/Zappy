/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** server.h
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include "my.h"
    #include "list.h"
    #include "network.h"
    #include "map.h"
    #include "player.h"
    #include "utils.h"

    #define MAX_CONNECTIONS 1024

typedef struct {
    int socket_fd;
    struct sockaddr_in sockaddr;
    socklen_t len;
    player_t *player;
} client_t;

typedef struct {
    int socket_fd;
    struct sockaddr_in sockaddr;
    fd_set readfds;
    int last_fd;
    node *clients;
    node *commands;
} server_t;

server_t *create_server(int port);
void handle_client(server_t *server, args_t *args);

#endif /* !SERVER_H_ */
