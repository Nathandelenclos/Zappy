/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** map/generate.c
*/

#include "map.h"

/**
 * Create a tile.
 * @return The tile.
 */
map_t *create_tile(void)
{
    map_t *tile = malloc(sizeof(map_t));

    if (tile == NULL)
        return NULL;
    tile->tile = malloc(sizeof(tile_t));
    if (tile->tile == NULL)
        return NULL;
    tile->tile->items = NULL;
    tile->up = NULL;
    tile->down = NULL;
    tile->left = NULL;
    tile->right = NULL;
    return tile;
}

/**
 * Generate x tiles (x is the total size so if x == 1 no tile will be created).
 * @param tile - The tile.
 * @param x - The x size.
 */
void generate_x_tiles(map_t *tile, int x)
{
    map_t *tmp = tile;

    if (x == 1) {
        tile->right = tile;
        tile->left = tile;
        return;
    }
    for (int i = 1; i < x; i++) {
        tmp->right = create_tile();
        tmp->right->left = tmp;
        tmp = tmp->right;
    }
    tmp->right = tile;
    tile->left = tmp;
}

/**
 * link two part of a map up and down, they must be the same size.
 * @param first - The first part of the map.
 * @param second - The second part of the map.
 */
void link_up_down(map_t *first, map_t *second)
{
    map_t *tmp_first = first;
    map_t *tmp_second = second;

    while (tmp_first->down == NULL && tmp_second->up == NULL) {
        tmp_first->down = tmp_second;
        tmp_second->up = tmp_first;
        if (tmp_first->right == NULL || tmp_second->right == NULL)
            break;
        tmp_first = tmp_first->right;
        tmp_second = tmp_second->right;
    }
}

/**
 * Generate a map.
 * @param x - The x size.
 * @param y - The y size.
 * @return The map.
 */
map_t *generate_map(int x, int y)
{
    map_t **tmp_map = MALLOC(sizeof(map_t *) * y);

    if (x <= 0 || y <= 0)
        return NULL;
    for (int i = 0; i < y; ++i) {
        tmp_map[i] = create_tile();
        generate_x_tiles(tmp_map[i], x);
    }
    for (int i = 0; i < y - 1; ++i) {
        link_up_down(tmp_map[i], tmp_map[i + 1]);
    }
    link_up_down(tmp_map[y - 1], tmp_map[0]);
    return tmp_map[0];
}
