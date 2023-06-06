/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** network/create_server.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../../include/server.h"

Test(create_server, test_case_name)
{
    args_t args;
    server_t *server = create_server(&args);

    cr_assert_not_null(server, "Server is NULL");

    cr_assert_null(server->commands, "Commands should be NULL");
    cr_assert_null(server->clients, "Clients should be NULL");
    cr_assert(server->socket_fd >= 0, "Invalid socket file descriptor");
    cr_assert(server->is_running, "Server should be running");
}
