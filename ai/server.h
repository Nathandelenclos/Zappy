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


typedef enum { //david ajouts
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
} inventory_e;

typedef struct {
    inventory_e obj;
    int quantity;
} inventory_t;

typedef struct {
    int socket_fd;
    struct sockaddr_in sockaddr;
    socklen_t len;
    //david ajouts
    inventory_t *inventory; //index de 0 a 6 avec enum inventory
    char *command_buffer; //index 0 = command en cours ou a executer en 1er creer fonction pop et append
} client_t;

typedef struct { //david ajouts
    node *clients;
    char *name;
    int nb_connections;
} teams_t;

typedef struct {
    int socket_fd;
    struct sockaddr_in sockaddr;
    node *clients;
    fd_set readfds;
    int last_fd;
    node *client;
    node *commands;
    //david ajouts
    int freq;
    int port;
    node *teams;
} server_t;

#endif /* !SERVER_H_ */
