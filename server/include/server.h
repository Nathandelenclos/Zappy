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
    #include "cmd.h"
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

struct client_s {
    int socket_fd;
    struct sockaddr_in sockaddr;
    socklen_t len;
    player_t *player;
    STATE_CONNECTION state;
    string team;
    team_type_t type;
    node *commands;
};

struct server_s {
    args_t *args;
    int socket_fd;
    struct sockaddr_in sockaddr;
    fd_set readfds;
    int last_fd;
    bool is_running;
    timestamp_t time;
    cmd_queue_t *cmd_queue;
    node *clients;
    node *teams;
    map_t *map;
};

typedef struct {
    string command;
    int time;
    void (*func)(server_t *server, cmd_t *cmd);
    void (*func_start)(server_t *server, cmd_t *cmd);
} command_t;

server_t *create_server(args_t *args);
void handle_client(server_t *server);
void new_connection(server_t *server);
client_t *create_client(server_t *server);
void handle_action(server_t *server);
void new_player(server_t *server, client_t *client);
void randomize_items(server_t *server);
int get_item_count(node *inventory, item_type_t type);
void add_item_to_inventory(node **inventory, item_type_t item_type);
void remove_item_from_inventory(node **inventory, item_type_t item_type);

static command_t commands_ai[] = {
    {"Forward", 7, forward, NULL},
    {"Right", 7, right, NULL},
    {"Left", 7, left, NULL},
    {"Look", 7, look, NULL},
    {"Inventory", 1, inventory, NULL},
    {"Broadcast", 7, debug_cmd, NULL},
    {"Connect_nbr", 0, debug_cmd, NULL},
    {"Fork", 42, debug_cmd, NULL},
    {"Eject", 7, debug_cmd, NULL},
    {"Take", 7, take, NULL},
    {"Set", 7, set, NULL},
    {"Incantation", 300, incantation, incantation_start},
    {NULL, 0, NULL, NULL}
};

static command_t commands_gui[] = {
    {NULL, 0, NULL, NULL}
};

#endif /* !SERVER_H_ */
