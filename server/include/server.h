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

typedef struct {
    string name;
    node *clients;
    node *eggs_places;
    team_type_t type;
} team_t;

struct client_s {
    int socket_fd;
    struct sockaddr_in sockaddr;
    socklen_t len;
    player_t *player;
    STATE_CONNECTION state;
    team_t *team;
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
    int map_width;
    int map_height;
};

typedef struct {
    string command;
    int time;
    void (*func)(server_t *server, cmd_t *cmd);
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
void add_items_to_inventory(node **inventory, item_type_t item_type, int quantity);
bool remove_item_from_inventory(node **inventory, item_type_t item_type);
void new_command(server_t *server, client_t *client, command_t command, string command_str);
map_t *random_place(server_t *server, item_type_t type);
node *random_places(server_t *server, item_type_t type, int quantity);
void new_event(server_t *server, client_t *client, command_t command);
string read_message(client_t *client);
void find_command(server_t *server, client_t *client, string command);
node *player_to_client(server_t *server, node *players);
void pause_activity(server_t *server, node *clients);
void resume_activity(server_t *server, node *clients);
node *get_players_on_tile_with_level(cmd_t *cmd, int level);
node *get_players_on_tile(cmd_t *cmd);

static const command_t commands_ai[] = {
    {"Forward", 7, forward},
    {"Right", 7, right},
    {"Left", 7, left},
    {"Look", 7, look},
    {"Inventory", 1, inventory},
    {"Broadcast", 7, broadcast},
    {"Connect_nbr", 0, connect_nbr},
    {"Fork", 42, fork_cmd},
    {"Take", 7, take},
    {"Set", 7, set},
    {"Incantation", 0, incantation_start},
    {NULL, 0, NULL}
};

static const command_t commands_gui[] = {
    {"msz", 0, msz},
    {NULL, 0, NULL}
};

#endif /* !SERVER_H_ */
