/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** network/actions.c
*/

#include "server.h"

/**
 * Read message.
 * @param client - The client.
 * @return The message.
 */
string read_message(client_t *client)
{
    char buffer[1024] = {0};
    int valread = read(client->socket_fd, buffer, 1024);
    if (valread == 0) {
        return NULL;
    }
    string have_return = strstr(buffer, "\n");
    string have_return2 = strstr(buffer, "\r");
    if (have_return != NULL)
        have_return[0] = '\0';
    if (have_return2 != NULL)
        have_return2[0] = '\0';
    return my_strdup(buffer);
}

/**
 * New command.
 * @param server - The server.
 * @param client - The client.
 * @param command - The command.
 */
void new_command(server_t *server, client_t *client, command_t command)
{
    cmd_t *cmd = create_cmd(
        client,
        my_strdup(command.command),
        server->time,
        server->time + (command.time != 0 ?
            (((command.time  * 1000) / server->args->freq)) : 0),
        command.func);
    if (client->commands != NULL) {
        cmd_t *last_cmd = client->commands->data;
        if (last_cmd->state != FINISHED) {
            cmd->state = NOT_STARTED;
            cmd->timestamp_start = last_cmd->timestamp_end;
            cmd->timestamp_end = cmd->timestamp_start + (command.time != 0
                    ? ((command.time * 1000) / server->args->freq) : 0);
        }
    }
    put_in_list(&client->commands, cmd);
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
            new_command(server, client, commands[i]);
            return;
        }
    }
    dprintf(client->socket_fd, KO);
}

/**
 * Handle action.
 * @param server - The server.
 * @param client - The client.
 */
void new_graphic_client(server_t *server, client_t *client)
{
    client->type = GUI;
    client->state = WAITING_COMMAND;
    dprintf(client->socket_fd, "%d\n%d %d\n", server->args->clients_nb,
        server->args->width, server->args->height);
}

/**
 * New ai client.
 * @param server - The server.
 * @param client - The client.
 * @param action - The action.
 */
void new_ai_client(server_t *server, client_t *client, string action)
{
    client->type = AI;
    node *team = search_in_list_by(server->teams, action, search_by_string);
    client->team = team == NULL ? NULL : team->data;
    if (client->team == NULL) {
        dprintf(client->socket_fd, KO);
        return;
    }
    client->state = WAITING_COMMAND;
    new_player(server, client);
    dprintf(client->socket_fd, "%d\n%d %d\n", server->args->clients_nb,
        server->args->width, server->args->height);
}

/**
 * Handle action.
 * @param server - The server.
 * @param client - The client.
 */
void action(server_t *server, client_t *client)
{
    string action = read_message(client);
    if (action == NULL) {
        return;
    }
    if (client->state == WAITING_TEAM_NAME) {
        if (strcmp(action, GRAPHIC) == 0) {
            new_graphic_client(server, client);
            return;
        }
        new_ai_client(server, client, action);
    } else if (client->state == WAITING_COMMAND) {
        find_command(server, client, action);
    }
    FREE(action);
}

/**
 * Handle client.
 * @param server - The server.
 */
void handle_action(server_t *server)
{
    if (!(server->is_running)) {
        return;
    }
    for (node *tmp = server->clients; tmp != NULL; tmp = tmp->next) {
        client_t *client = (client_t *) tmp->data;
        if (FD_ISSET(client->socket_fd, &server->readfds)) {
            action(server, client);
        }
    }
}
