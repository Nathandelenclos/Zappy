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
    #include "map.h"
    #include "player.h"
    #include "utils.h"
    #include "message.h"
    #include "commands.h"
    #include <stdbool.h>
    #include <arpa/inet.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <errno.h>
    #include <time.h>

    #define MAX_CONNECTIONS 1024

typedef unsigned long long timestamp_t;

typedef enum {
    WAITING_TEAM_NAME,
    WAITING_COMMAND,
} STATE_CONNECTION;

typedef enum {
    GUI,
    AI,
    NONE,
} team_type_t;

typedef struct {
    int socket_fd;
    struct sockaddr_in sockaddr;
    socklen_t len;
    player_t *player;
    STATE_CONNECTION state;
    string team;
    team_type_t type;
} client_t;

typedef struct {
    args_t *args;
    int socket_fd;
    struct sockaddr_in sockaddr;
    fd_set readfds;
    int last_fd;
    bool is_running;
    timestamp_t time;
    node *clients;
    node *commands;
    node *teams;
    map_t *map;
} server_t;

typedef struct {
    string name;
    team_type_t type;
    void (*func)(server_t *server, client_t *client, string command);
} command_t;

server_t *create_server(args_t *args);
void handle_client(server_t *server);
void new_connection(server_t *server);
client_t *create_client(server_t *server);
void handle_action(server_t *server);
void new_player(server_t *server, client_t *client);
void randomize_items(server_t *server);

static command_t commands_ai[] = {
    {NULL, NONE, NULL}
};

static command_t commands_gui[] = {
    {NULL, NONE, NULL}
};

#endif /* !SERVER_H_ */
