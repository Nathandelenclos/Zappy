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

typedef enum {
    PLAYER,
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    EGG
} item_type_t;

static const string item_type_str[] = {
    "player",
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame",
    "egg",
    NULL
};

typedef struct {
    item_type_t type;
    double density;
} type_density_t;

typedef struct {
    item_type_t type;
} item_t;

static const type_density_t type_density[] = {
    {FOOD, 0.5},
    {LINEMATE, 0.3},
    {DERAUMERE, 0.15},
    {SIBUR, 0.1},
    {MENDIANE, 0.1},
    {PHIRAS, 0.08},
    {THYSTAME, 0.05},
    {PLAYER, 0.0}
};

#endif /* !ITEM_H_ */
