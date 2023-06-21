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
    WEST,
    SOUTH,
    EAST
} direction_t;

typedef struct {
    item_type_t type;
    node *inventory;
    int level;
    map_t *map;
    node *commands;
    direction_t direction;
    bool alive;
} player_t;

typedef struct {
    int nb_player;
    int nb_linemate;
    int nb_deraumere;
    int nb_sibur;
    int nb_mendiane;
    int nb_phiras;
    int nb_thystame;
} evolution_t;

static const int evolutions[7][8] = {
    // nb_player, nb_food, nb_linemate, nb_deraumere, nb_sibur, nb_mendiane, nb_phiras, nb_thystame
    {1, 0, 1, 0, 0, 0, 0, 0},
    {2, 0, 1, 1, 1, 0, 0, 0},
    {2, 0, 2, 0, 1, 0, 2, 0},
    {4, 0, 1, 1, 2, 0, 1, 0},
    {4, 0, 1, 2, 1, 3, 0, 0},
    {6, 0, 1, 2, 3, 0, 1, 0},
    {6, 0, 2, 2, 2, 2, 2, 1}
};

#endif /* !PLAYER_H_ */
