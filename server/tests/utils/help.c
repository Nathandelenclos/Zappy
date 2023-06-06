/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** utils/help.c
*/

#include "../../include/utils.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect_all_stdout(void)
{
        cr_redirect_stdout();
        cr_redirect_stderr();
}

Test(help, test_help_output, .init = redirect_all_stdout)
{
    help();
    cr_assert_stdout_eq_str("USAGE: ./zappy_server -p port -x width -y height -n name1"
           " name2 ... -c clientsNb -f freq\n"
           "    port is the port number\n"
           "    width is the width of the world\n"
           "    height is the height of the world\n"
           "    nameX is the name of the team X\n"
           "    clientsNb is the number of authorized clients per team\n"
           "    freq is the reciprocal of time unit for execution of actions");
}


