/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** utils/help.c
*/

#include "../../include/utils.h"
#include "criterion/criterion.h"
#include "criterion/redirect.h"

Test(args_init, args_init_test)
{
    args_t *args = args_init();
    cr_assert_not_null(args);
    cr_assert_eq(args->port, 0);
    cr_assert_eq(args->width, 0);
    cr_assert_eq(args->height, 0);
    cr_assert_eq(args->clients_nb, 0);
    cr_assert_eq(args->freq, 0);
    cr_assert_null(args->teams);
}

Test(args_parsed, args_parsed_regular_test)
{
    char *argv[15] = {"./zappy_server", "-p", "4242", "-x", "10",
        "-y", "10", "-n", "toto", "tata", "-c", "10", "-f", "2",NULL};
    args_t *args = args_parsed(args_init(), 14, argv);
    cr_assert_eq(args->port, 4242);
    cr_assert_eq(args->width, 10);
    cr_assert_eq(args->height, 10);
    cr_assert_eq(args->clients_nb, 10);
    cr_assert_eq(args->freq, 2);
    cr_assert_not_null(args->teams);
    cr_assert_str_eq(args->teams->data, "tata");
    cr_assert_str_eq(args->teams->next->data, "toto");
}

Test(args_parsed, args_parsed_unordoned_test)
{
    char *argv[15] = {"./zappy_server", "-y", "10","-p", "4242", "-x", "10",
        "-f", "2", "-c", "10", "-n", "toto", "tata", NULL};
    args_t *args = args_parsed(args_init(), 12, argv);
    cr_assert_eq(args->port, 4242);
    cr_assert_eq(args->width, 10);
    cr_assert_eq(args->height, 10);
    cr_assert_eq(args->clients_nb, 10);
    cr_assert_eq(args->freq, 2);
    cr_assert_not_null(args->teams);
    cr_assert_str_eq(args->teams->data, "tata");
    cr_assert_str_eq(args->teams->next->data, "toto");
}

Test(args_parsed, args_parsed_error_test)
{
    args_t *args = args_init();
    char *argv[15] = {"./zappy_server", "-y", "10","-p", "4242", "-x", "10",
        "-f", "2", "-c", "10", "-n", "toto", "tata", NULL};
    args = args_parsed(args, 12, argv);
    cr_assert_eq(args->port, 4242);
    cr_assert_eq(args->width, 10);
    cr_assert_eq(args->height, 10);
    cr_assert_eq(args->clients_nb, 10);
    cr_assert_eq(args->freq, 2);
    cr_assert_not_null(args->teams);
    cr_assert_str_eq(args->teams->data, "tata");
    cr_assert_str_eq(args->teams->next->data, "toto");
}
