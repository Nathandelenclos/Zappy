/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** player.h
*/

#ifndef PLAYER_H_
    #define PLAYER_H_

    #include "my.h"
    #include "list.h"
    #include "map.h"

typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
} direction_t;

typedef struct {
    item_type_t type;
    node *inventory;
    int level;
    map_t *map;
    node *commands;
    direction_t direction;
} player_t;

#endif /* !PLAYER_H_ */
