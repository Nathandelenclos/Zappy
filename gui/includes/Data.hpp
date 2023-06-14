/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** Data.hpp
*/

#pragma once

#include <iostream>
#include <vector>

namespace zappy_gui {

    class Cell {
        public:
            int x = 0;
            int y = 0;
            std::vector<int> resources;
    };

    class Data {
        public:
            int width;
            int height;
            size_t frequency;
            std::vector<std::string> teams;
            std::vector<std::vector<Cell>> grid;
            std::string message;
    };

}
