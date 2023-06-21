/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** utils/help.c
*/

#include <stdio.h>
#include "utils.h"
#include "message.h"

/**
 * Display the help message.
 */
void help()
{
    printf(HELP);
    FREE_ALL();
    exit(0);
}
