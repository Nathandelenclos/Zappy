/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** Core.hpp
*/

#pragma once

#include "Includes.hpp"
#include "Doader.hpp"

namespace zappy_gui {

    class Core {
        public:
            Core();
            ~Core();

            void findLibraries();
            void setData(Data data);

            void displayWindow();

        protected:
            std::vector<std::string> _libraries;
            Data _data;
        private:
            GraphicalLoaderPtr _loader;
    };

}
