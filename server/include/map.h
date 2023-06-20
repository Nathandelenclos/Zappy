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
    #include "item.h"

typedef struct {
    node *items;
} tile_t;

typedef struct map_s map_t;

struct map_s {
    tile_t *tile;
    int pos_x;
    int pos_y;
    struct map_s *up;
    struct map_s *down;
    struct map_s *left;
    struct map_s *right;
};

map_t *create_tile(void);
void generate_x_tiles(map_t *tile, int x, int y);
void link_up_down(map_t *first, map_t *second);
map_t *generate_map(int x, int y);

#endif /* !MAP_H_ */
