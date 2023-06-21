/*
** EPITECH PROJECT, 2023
** Network
** File description:
** strdup
*/

#include "list.h"
#include <string.h>

/**
 * strdup with my_malloc for garbage collector.
 * @param data
 * @return
 */
char *my_strdup(char *data)
{
    int len = strlen(data);
    char *ret = MALLOC(sizeof(char) * len + 1);
    for (int i = 0; i <= len; ++i) {
        ret[i] = data[i];
    }
    return ret;
}
