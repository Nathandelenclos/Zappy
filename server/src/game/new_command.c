/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** network/actions.c
*/

#include "server.h"

/**
 * New command.
 * @param server - The server.
 * @param client - The client.
 * @param command - The command.
 * @param command_str - The command str.
 */
void new_command(server_t *server, client_t *client, command_t command,
    string command_str)
{
    cmd_t *cmd = create_cmd(client, my_strdup(command_str),
        server->time,
        server->time + (command.time != 0 ?
            (((command.time * 1000) / server->args->freq)) : 0),
        command.func);
    cmd->ticks = command.time;
    if (client && client->commands) {
        cmd_t *last_cmd = client->commands->data;
        if (last_cmd->state != FINISHED && last_cmd->state != PAUSE) {
            cmd->state = NOT_STARTED;
            cmd->timestamp_start = last_cmd->timestamp_end;
            cmd->timestamp_end = cmd->timestamp_start + (command.time != 0
                ? ((command.time * 1000) / server->args->freq) : 0);
        }
    }
    if (client) {
        put_in_list(&client->commands, cmd);
    }
    add_cmd(cmd, &server->cmd_queue);
}

/**
 * New command.
 * @param server - The server.
 * @param client - The client.
 * @param command - The command.
 * @param command_str - The command str.
 */
void new_event(server_t *server, client_t *client, command_t command)
{
    cmd_t *cmd = create_cmd(client, my_strdup(""),
        server->time,
        server->time + (command.time != 0 ?
            (((command.time * 1000) / server->args->freq)) : 0),
        command.func);
    cmd->state = NOT_FOLLOWED;
    add_cmd(cmd, &server->cmd_queue);
}

/**
 * Find command.
 * @param server - The server.
 * @param client - The client.
 * @param command - The command.
 */
void find_command(server_t *server, client_t *client, string command)
{
    command_t *commands = client->type == GUI ? commands_gui : commands_ai;
    for (int i = 0; commands[i].command != NULL; i++) {
        if (strstr(command, commands[i].command) != NULL) {
            new_command(server, client, commands[i], command);
            return;
        }
    }
    dprintf(client->socket_fd, KO);
}
