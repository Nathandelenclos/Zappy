/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** game/commands/test.h
*/

#include "server.h"

/**
 * Debug cmd.
 * @param server - The server.
 * @param cmd - The cmd.
 */
void debug_cmd(server_t *server, cmd_t *cmd)
{
    dprintf(cmd->client->socket_fd, "%s result time start = %llu | time end = %llu | actual time = %llu\n", cmd->cmd,  cmd->timestamp_start, cmd->timestamp_end, server->time);
    printf( "%s result time start = %llu | time end = %llu | actual time = %llu\n", cmd->cmd, cmd->timestamp_start, cmd->timestamp_end, server->time);
}

