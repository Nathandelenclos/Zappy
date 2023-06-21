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

typedef struct {
    item_type_t type;
    node *inventory;
    int level;
    map_t *map;
    node *commands;
} player_t;

#endif /* !PLAYER_H_ */
