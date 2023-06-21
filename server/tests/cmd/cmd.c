/*
** EPITECH PROJECT, 2023
** server
** File description:
** cmd.c
*/
#include <criterion/criterion.h>
#include "../../include/cmd.h"
#include "../../include/server.h"

Test(cmd, create_cmd)
{
    client_t *client_socket = MALLOC(sizeof(client_t));
    cmd_t *cmd = create_cmd(client_socket, NULL, 0, 0, NULL);

    cr_assert_eq(cmd->client, client_socket);
    cr_assert_eq(cmd->timestamp_start, 0);
    cr_assert_eq(cmd->timestamp_end, 0);
    cr_assert_eq(cmd->state, STARTED);
}

Test(cmd, add_cmd)
{
    client_t *client_socket = MALLOC(sizeof(client_t));
    cmd_t *cmd = create_cmd(client_socket, NULL, 0, 0, NULL);;
    cmd_queue_t *queue = NULL;

    add_cmd(cmd, &queue);
    cr_assert_eq(queue->data, cmd);
}

Test(cmd, add_cmd_sorted)
{
    client_t *client_socket = MALLOC(sizeof(client_t));
    cmd_t *cmd1 = create_cmd(client_socket, NULL, 0, 0, NULL);
    cmd_t *cmd2 = create_cmd(client_socket, NULL, 1, 1, NULL);
    cmd_queue_t *queue = NULL;

    add_cmd(cmd1, &queue);
    add_cmd(cmd2, &queue);
    cr_assert_eq(queue->data, cmd1);
    cr_assert_eq(queue->next->data, cmd2);
}

Test(cmd, add_cmd_sorted2)
{
    client_t *client_socket = MALLOC(sizeof(client_t));
    cmd_t *cmd1 = create_cmd(client_socket, NULL, 1, 1, NULL);;
    cmd_t *cmd2 = create_cmd(client_socket, NULL, 0, 0, NULL);;
    cmd_queue_t *queue = NULL;

    add_cmd(cmd1, &queue);
    add_cmd(cmd2, &queue);
    cr_assert_eq(queue->data, cmd2);
    cr_assert_eq(queue->next->data, cmd1);
}

Test(cmd, add_cmd_sorted_advanced)
{
    client_t *client_socket = MALLOC(sizeof(client_t));
    cmd_t *cmd1 = create_cmd(client_socket, NULL, 0, 0, NULL);;
    cmd_t *cmd2 = create_cmd(client_socket, NULL, 1, 1, NULL);;
    cmd_t *cmd3 = create_cmd(client_socket, NULL, 2, 2, NULL);;
    cmd_queue_t *queue = NULL;

    add_cmd(cmd2, &queue);
    add_cmd(cmd1, &queue);
    add_cmd(cmd3, &queue);
    cr_assert_eq(queue->data, cmd1);
    cr_assert_eq(queue->next->data, cmd2);
    cr_assert_eq(queue->next->next->data, cmd3);
}

Test(cmd, add_cmd_sorted_advanced_2)
{
    client_t *client_socket = MALLOC(sizeof(client_t));
    cmd_t *cmd1 = create_cmd(client_socket, NULL, 0, 0, NULL);;
    cmd_t *cmd1_2 = create_cmd(client_socket, NULL, 0, 0, NULL);;
    cmd_t *cmd2 = create_cmd(client_socket, NULL, 1, 1, NULL);;
    cmd_t *cmd2_2 = create_cmd(client_socket, NULL, 1, 1, NULL);;
    cmd_t *cmd3 = create_cmd(client_socket, NULL, 2, 2, NULL);;
    cmd_t *cmd3_2 = create_cmd(client_socket, NULL, 2, 2, NULL);;
    cmd_queue_t *queue = NULL;

    add_cmd(cmd2, &queue);
    add_cmd(cmd1, &queue);
    add_cmd(cmd3, &queue);
    add_cmd(cmd2_2, &queue);
    add_cmd(cmd1_2, &queue);
    add_cmd(cmd3_2, &queue);
    cr_assert(queue->data == cmd1 || queue->data == cmd1_2);
    cr_assert(queue->next->next->data == cmd2 || queue->next->next->data == cmd2_2);
    cr_assert(queue->next->next->next->next->data == cmd3 || queue->next->next->next->next->data == cmd3_2);

    // check_size
    int size = 0;
    cmd_queue_t *tmp = queue;
    while (tmp) {
        size++;
        tmp = tmp->next;
    }
    cr_assert_eq(size, 6);
}
