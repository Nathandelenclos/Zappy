/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

/**
 * Init args struct.
 */
args_t *args_init()
{
    args_t *args = malloc(sizeof(args_t));
    args->port = 0;
    args->width = 0;
    args->height = 0;
    args->freq = 0;
    args->clients_nb = 0;
    args->teams = NULL;
    return args;
}

/**
 * Put the team name in the list.
 * @param args - The args struct.
 * @param argc - Argument count.
 * @param argv - Argument vector.
 * @param i - The index.
 * @return The args struct.
 */
args_t *args_team_name(args_t *args, int argc, char **argv, int i)
{
    if (strcmp(argv[i], "-n") == 0 && argv[i + 1] != NULL) {
            while (argv[i] != NULL && argv[i + 1] != NULL && strcmp(argv[i + 1], "-c") != 0 &&
                   strcmp(argv[i + 1], "-f") != 0 && strcmp(argv[i + 1], "-p") != 0 &&
                     strcmp(argv[i + 1], "-x") != 0 && strcmp(argv[i + 1], "-y") != 0) {
                put_in_list(&args->teams, argv[i + 1]);
                i++;
            }
        }
    return args;
}

/**
 * Parse the arguments.
 * @param args - The args struct.
 * @param argc - Argument count.
 * @param argv - Argument vector.
 * @return The args struct.
 */
args_t *args_parsed(args_t *args, int argc, char **argv)
{
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "-help") == 0)
            help();
        if (strcmp(argv[i], "-p") == 0 && argv[i + 1] != NULL)
            args->port = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-x") == 0 && argv[i + 1] != NULL)
            args->width = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-y") == 0 && argv[i + 1] != NULL)
            args->height = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-c") == 0 && argv[i + 1] != NULL)
            args->clients_nb = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-f") == 0 && argv[i + 1] != NULL)
            args->freq = atoi(argv[i + 1]);
        args = args_team_name(args, argc, argv, i);
    }
    return args;
}
