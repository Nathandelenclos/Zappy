/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** item.h
*/

#ifndef ITEM_H_
    #define ITEM_H_

    #include "my.h"
    #include "list.h"
    #include "network.h"

typedef enum {
    PLAYER,
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} item_type_t;

typedef struct {
    item_type_t name;
} item_t;

#endif /* !ITEM_H_ */
