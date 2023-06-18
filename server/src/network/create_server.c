/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** network/create_server.c
*/

#include <unistd.h>
#include "server.h"

/**
 * Init socket address
 * @param server - Server to init.
 * @param port - Port to init.
 */
void init_socketaddr(server_t *server, int port)
{
    memset(&server->sockaddr, 0, sizeof(server->sockaddr));
    server->sockaddr.sin_family = AF_INET;
    server->sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    server->sockaddr.sin_port = htons(port);
}

/**
 * Init networking.
 * @param server - Server to init.
 * @return - Return server.
 */
server_t *init_networking(server_t *server)
{
    int ret;
    server->socket_fd = socket(AF_INET, SOCK_STREAM, 0);;
    if (server->socket_fd < 0) {
        perror("socket()");
        exit(EXIT_FAILURE);
    }
    init_socketaddr(server, server->args->port);
    ret = bind(server->socket_fd, (struct sockaddr *) &server->sockaddr,
        sizeof(server->sockaddr));
    if (ret < 0) {
        perror_exit("bind()");
    }
    ret = listen(server->socket_fd, MAX_CONNECTIONS);
    if (ret < 0) {
        perror_exit("listen()");
    }
    return server;
}

/**
 * Create server.
 * @param port - Port to listen.
 * @return - Return server fd.
 */
server_t *create_server(args_t *args)
{
    server_t *server = MALLOC(sizeof(server_t));
    server->args = args;
    server->is_running = true;
    server->clients = NULL;
    server->cmd_queue = NULL;
    server->teams = args->teams;
    server = init_networking(server);
    server->map = generate_map(args->width, args->height);
    server->time = 0;
    randomize_items(server);
    return server;
}
