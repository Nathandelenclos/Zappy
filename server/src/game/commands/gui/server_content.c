/*
** EPITECH PROJECT, 2023
** server
** File description:
** server_content.c
*/
#include "server.h"

/**
 * Get the names of all the teams.
 * @param server - The server.
 * @param cmd - The cmd.
 */
void tna(server_t *server, cmd_t *cmd)
{
    node *team = server->teams;
    team_t *tmp = NULL;
    char buffer[10000] = {0};
    int offset = 0;

    (void)cmd;
    while (team != NULL) {
        tmp = (team_t *)team->data;
        if (strcmp(tmp->name, "GRAPHIC") == 0)
            continue;
        offset += snprintf(buffer + offset,
           sizeof(buffer) - offset,"tna %s\n", tmp->name);
        team = team->next;
    }
    write(cmd->client->socket_fd, buffer, offset);
}

/**
 * Get the current time unit.
 * @param server - The server.
 * @param cmd - The cmd.
 */
void sgt(server_t *server, cmd_t *cmd)
{
    (void)cmd;
    dprintf(cmd->client->socket_fd, "sgt %d\n", server->args->freq);
}

/**
 * Change the current time unit.
 * @param server - The server.
 * @param cmd - The cmd.
 */
void sst(server_t *server, cmd_t *cmd)
{
    parse_cmd_arg(cmd->cmd, true);
    int freq = parse_cmd_arg(cmd->cmd, false);

    if (freq <= -1) {
        dprintf(cmd->client->socket_fd, "sbp\n");
        return;
    }
    server->args->freq = freq;
    dprintf(cmd->client->socket_fd, "sst %d\n", freq);
}