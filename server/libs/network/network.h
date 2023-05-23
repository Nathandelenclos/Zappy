/*
** EPITECH PROJECT, 2023
** NetworkLib
** File description:
** network.h
*/

#include "my.h"
#include "list.h"
#include "code.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#ifndef NETWORK_H
    #define NETWORK_H

typedef struct sockaddr_in sockaddr_in_t;

typedef struct {
    int code;
    int len;
    string data;
} packet_t;

string my_strdup(string data);
packet_t *read_packet(int fd);
int send_packet(int fd, packet_t *socket);
packet_t *create_packet(int code, string data);
int create_socket(void);
sockaddr_in_t create_sockaddr_in(int port, string ip);
string new_uuid(void);

#endif
