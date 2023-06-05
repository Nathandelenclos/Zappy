/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** utils.h
*/

#ifndef ZAPPY_UTILS_H
    #define ZAPPY_UTILS_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include "list.h"

typedef struct {
    int port;
    int width;
    int height;
    int freq;
    int clients_nb;
    node *teams;
} args_t;

void perror_exit(char *str);
void help();
args_t *args_init();
args_t *args_parsed(args_t *args, int argc, char **argv);

#endif //ZAPPY_UTILS_H
