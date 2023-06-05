/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** utils/help.c
*/

#include <stdio.h>
#include "utils.h"

/**
 * Display the help message.
 */
void help()
{
    printf("USAGE: ./zappy_server -p port -x width -y height -n name1"
           " name2 ... -c clientsNb -f freq\n"
           "    port is the port number\n"
           "    width is the width of the world\n"
           "    height is the height of the world\n"
           "    nameX is the name of the team X\n"
           "    clientsNb is the number of authorized clients per team\n"
           "    freq is the reciprocal of time unit for execution of actions");
    FREE_ALL();
    exit(0);
}
