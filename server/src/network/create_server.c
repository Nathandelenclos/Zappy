/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** network/create_server.c
*/

#include <unistd.h>
#include "network.h"
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
 * Create server.
 * @param port - Port to listen.
 * @return - Return server fd.
 */
server_t *create_server(args_t *args)
{
    server_t *server = MALLOC(sizeof(server_t));
    server->commands = NULL;
    server->clients = NULL;
    server->socket_fd = create_socket();
    server->is_running = true;
    init_socketaddr(server, args->port);
    int ret;
    ret = bind(server->socket_fd, (struct sockaddr *) &server->sockaddr,
        sizeof(server->sockaddr));
    if (ret < 0)
        perror_exit("bind()");
    ret = listen(server->socket_fd, MAX_CONNECTIONS);
    if (ret < 0)
        perror_exit("listen()");
    return server;
}
