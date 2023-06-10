/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** game/commands/test.h
*/

#include "server.h"

void test_exec(server_t *server, cmd_t *cmd)
{
    dprintf(cmd->client->socket_fd, "test result time start = %llu | time end = %llu | actual time = %llu\n", cmd->timestamp_start, cmd->timestamp_end, server->time);
    printf( "test result time start = %llu | time end = %llu | actual time = %llu\n", cmd->timestamp_start, cmd->timestamp_end, server->time);
    FREE(cmd->cmd);
    FREE(cmd);
}

void test(server_t *server, client_t *client, string command)
{

    add_cmd(create_cmd(
        client,
        my_strdup(command),
        server->time, server->time + ((7  * 1000) / server->args->freq),
        test_exec), &server->cmd_queue);
}


void test2(server_t *server, client_t *client, string command)
{

    add_cmd(create_cmd(
        client,
        my_strdup(command),
        server->time, server->time + ((2  * 1000) / server->args->freq),
        test_exec), &server->cmd_queue);
}
