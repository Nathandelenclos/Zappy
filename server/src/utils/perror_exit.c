/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** utils/perror_exit.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <list.h>

/**
 * Exit with perror and FREE_ALL.
 */
void perror_exit(char *str)
{
    perror(str);
    FREE_ALL();
    exit(EXIT_FAILURE);
}
