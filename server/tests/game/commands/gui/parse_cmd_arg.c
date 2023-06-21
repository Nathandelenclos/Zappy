/*
** EPITECH PROJECT, 2023
** server
** File description:
** parse_cmd_arg.c
*/
#include <criterion/criterion.h>
#include "../../../../include/server.h"

Test(parse_cmd_arg, should_return_1)
{
    char *cmd = "1";
    int res = parse_cmd_arg(cmd, true);

    cr_assert_eq(res, 1);
}

Test(parse_cmd_arg, advanced)
{
    char *cmd = "123 e 456";
    int res = parse_cmd_arg(cmd, true);

    cr_assert_eq(res, 123);

    res = parse_cmd_arg(cmd, false);

    cr_assert_eq(res, -1);

    res = parse_cmd_arg(cmd, false);

    cr_assert_eq(res, 456);
}
