/*
** EPITECH PROJECT, 2023
** server
** File description:
** test_map.c
*/
#include <criterion/criterion.h>
#include "../../include/map.h"

Test(map, test_create_tile)
{
    map_t *tile = create_tile();

    cr_assert(tile != NULL);
    cr_assert(tile->tile != NULL);
    cr_assert(tile->tile->items == NULL);
    cr_assert(tile->up == NULL);
    cr_assert(tile->down == NULL);
    cr_assert(tile->left == NULL);
    cr_assert(tile->right == NULL);
}

Test(map, test_generate_x_tiles)
{
    map_t *tile = create_tile();
    map_t *tmp = tile;

    generate_x_tiles(tile, 5);
    for (int i = 0; i < 5; ++i) {
        cr_assert(tmp->right != NULL);
        tmp = tmp->right;
    }
    // check circular
    cr_assert(tmp == tile);
}

Test(map, test_generate_x_tiles_left)
{
    map_t *tile = create_tile();
    map_t *tmp = tile;

    generate_x_tiles(tile, 5);
    for (int i = 0; i < 5; ++i) {
        cr_assert(tmp->left != NULL);
        tmp = tmp->left;
    }
    // check circular
    cr_assert(tmp == tile);
}

Test(map, test_generate_x_tiles_check_size)
{
    map_t *tile = create_tile();
    map_t *tmp = tile;
    int size = 1;

    generate_x_tiles(tile, 5);
    while (tmp->right != tile) {
        size++;
        tmp = tmp->right;
    }
    cr_assert(size == 5);
}

Test(map, test_link_up_down_basic)
{
    map_t *first = create_tile();
    map_t *second = create_tile();

    link_up_down(first, second);
    cr_assert(first->down == second);
    cr_assert(second->up == first);
}

Test(map, test_link_up_down_4_lines)
{
    map_t *first = create_tile();
    map_t *second = create_tile();
    map_t *third = create_tile();
    map_t *fourth = create_tile();

    link_up_down(first, second);
    link_up_down(second, third);
    link_up_down(third, fourth);
    link_up_down(fourth, first);
    cr_assert(first->down == second);
    cr_assert(second->down == third);
    cr_assert(third->down == fourth);
    cr_assert(fourth->down == first);
    cr_assert(first->up == fourth);
}

Test(map, test_link_up_down_multiple_tiles)
{
    map_t *first = create_tile();
    map_t *second = create_tile();
    generate_x_tiles(first, 5);
    generate_x_tiles(second, 5);

    link_up_down(first, second);
    cr_assert(first->down == second);
    cr_assert(second->up == first);
    cr_assert(first->right->down == second->right);
    cr_assert(second->right->up == first->right);
}

Test(map, test_creation_of_a_map_10_x_10)
{
    map_t *tmp_map[10];

    for (int i = 0; i < 10; ++i) {
        tmp_map[i] = create_tile();
        generate_x_tiles(tmp_map[i], 10);
    }
    for (int i = 0; i < 9; ++i) {
        link_up_down(tmp_map[i], tmp_map[i + 1]);
    }
    link_up_down(tmp_map[9], tmp_map[0]);

    cr_assert(tmp_map[0]->down == tmp_map[1]);
    cr_assert(tmp_map[1]->down == tmp_map[2]);
    cr_assert(tmp_map[2]->down == tmp_map[3]);
    cr_assert(tmp_map[3]->down == tmp_map[4]);
    cr_assert(tmp_map[4]->down == tmp_map[5]);
    cr_assert(tmp_map[5]->down == tmp_map[6]);
    cr_assert(tmp_map[6]->down == tmp_map[7]);
    cr_assert(tmp_map[7]->down == tmp_map[8]);
    cr_assert(tmp_map[8]->down == tmp_map[9]);
    cr_assert(tmp_map[9]->down == tmp_map[0]);

    map_t *tmp;

    // check right circular
    for (int i = 0; i < 10; i++) {
        tmp = tmp_map[i];
        for (int a = 0; a < 10; a++) {
            tmp = tmp->right;
        }
        cr_assert(tmp == tmp_map[i]);
    }

    // check down circular
    for (int i = 0; i < 10; i++) {
        tmp = tmp_map[0];
        for (int a = 0; a < 10; a++) {
            tmp = tmp->down;
        }
        cr_assert(tmp == tmp_map[0]);
        tmp_map[0] = tmp_map[0]->right;
    }
}


Test(map, test_creation_of_a_map_10_x_10_check_size)
{
    map_t *tmp_map[10];

    for (int i = 0; i < 10; ++i) {
        tmp_map[i] = create_tile();
        generate_x_tiles(tmp_map[i], 10);
    }
    for (int i = 0; i < 9; ++i) {
        link_up_down(tmp_map[i], tmp_map[i + 1]);
    }
    link_up_down(tmp_map[9], tmp_map[0]);

    // check size
    map_t *tmp;
    int size = 1;

    tmp = tmp_map[0];
    while(tmp->right != tmp_map[0]) {
        size++;
        tmp = tmp->right;
    }
    cr_assert(size == 10);

    size = 1;
    tmp = tmp_map[0];
    while(tmp->down != tmp_map[0]) {
        size++;
        tmp = tmp->down;
    }
    cr_assert(size == 10);
}

Test(map, test_creation_of_a_map_using_generation_function)
{
    map_t *map = generate_map(10, 10);
    map_t *tmp_map = map;
    map_t *tmp;

    cr_assert(map->down == map->right->down->left);
    // check right circular
    for (int i = 0; i < 10; i++) {
        tmp = tmp_map;
        for (int a = 0; a < 10; a++) {
            tmp = tmp->right;
        }
        cr_assert(tmp == tmp_map);
        tmp_map = tmp_map->down;
    }

    tmp_map = map;
    // check down circular
    for (int i = 0; i < 10; i++) {
        tmp = tmp_map;
        for (int a = 0; a < 10; a++) {
            tmp = tmp->down;
        }
        cr_assert(tmp == tmp_map);
        tmp_map = tmp_map->right;
    }

    tmp_map = map;
    // check left circular
    for (int i = 0; i < 10; i++) {
        tmp = tmp_map;
        for (int a = 0; a < 10; a++) {
            tmp = tmp->left;
        }
        cr_assert(tmp == tmp_map);
        tmp_map = tmp_map->down;
    }

    tmp_map = map;
    // check up circular
    for (int i = 0; i < 10; i++) {
        tmp = tmp_map;
        for (int a = 0; a < 10; a++) {
            tmp = tmp->up;
        }
        cr_assert(tmp == tmp_map);
        tmp_map = tmp_map->left;
    }
}

Test(map, test_creation_of_a_map_using_generation_function_size_1)
{
    map_t *map = generate_map(1, 1);

    cr_assert(map->down == map);
    cr_assert(map->up == map);
    cr_assert(map->left == map);
    cr_assert(map->right == map);
}

Test(map, test_creation_of_a_map_using_generation_function_size_2_1)
{
    map_t *map = generate_map(2, 1);

    cr_assert(map->down == map);
    cr_assert(map->up == map);
    cr_assert(map->left == map->right);
    cr_assert(map->right == map->left);
    cr_assert(map->right->down == map->right);
}

Test(map, test_creation_of_a_map_using_generation_function_size_1_2)
{
    map_t *map = generate_map(1, 2);

    cr_assert(map->down == map->up);
    cr_assert(map->up == map->down);
    cr_assert(map->left == map);
    cr_assert(map->right == map);
    cr_assert(map->down->right == map->down);
}

Test(map, test_creation_of_a_map_using_generation_function_size_0)
{
    map_t *map = generate_map(0, 2);

    cr_assert(map == NULL);

    map = generate_map(2, 0);

    cr_assert(map == NULL);
}

