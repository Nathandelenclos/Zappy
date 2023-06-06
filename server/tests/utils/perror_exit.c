/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** utils/perror_exit.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include <errno.h>
#include "../../include/utils.h"

void redirect_all_std(void)
{
    cr_redirect_stderr();
    cr_redirect_stdin();
}

Test(perror_exit, exits_with_failure, .exit_code = EXIT_FAILURE, .init = redirect_all_std)
{
    perror_exit("Test Error");
    cr_assert_stderr_eq_str("Test Error: ");
    cr_assert_stderr_eq_str(strerror(errno));
}
