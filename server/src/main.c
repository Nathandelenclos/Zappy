/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <server.h>
#include <signal.h>

void sigint_handler(int sig)
{
    (void )sig;
    FREE_ALL();
    exit(EXIT_SUCCESS);
}

/**
 * Main function.
 * @param argc - Argument count.
 * @param argv - Argument vector.
 * @return EXIT_SUCCESS if success, EXIT_FAILURE if error.
 */
int main(int argc, char **argv)
{
    srand(time(NULL));
    args_t *args = args_init();
    signal(SIGINT, sigint_handler);
    args = args_parsed(args, argc, argv);
    server_t *server = create_server(args);
    if (server == NULL)
        perror_exit("create_server");
    handle_client(server);
    FREE_ALL();
    return EXIT_SUCCESS;
}
