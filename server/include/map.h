/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** map.h
*/

#ifndef MAP_H_
    #define MAP_H_

    #include "my.h"
    #include "list.h"
    #include "network.h"
    #include "item.h"
    #include "player.h"

typedef struct {
    node *items;
} tile_t;

typedef struct map_s map_t;

struct map_s {
    tile_t *tile;
    struct map_s *up;
    struct map_s *down;
    struct map_s *left;
    struct map_s *right;
};

#endif /* !MAP_H_ */
