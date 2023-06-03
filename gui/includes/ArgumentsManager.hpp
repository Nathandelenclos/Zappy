/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** ArgumentsManager.hpp
*/

#pragma once

#include "Exception.hpp"

namespace zappy_gui {

    class ArgumentsManager {
        public:
            ArgumentsManager(int argc, char **argv);
            ~ArgumentsManager() = default;

            void checkArguments();

            int getPort() const { return _port; }
            std::string getMachine() const { return _machine; }

        protected:
            int _ac;
            char **_av;
        private:
            std::string _help;
            int _port{};
            std::string _machine;

    };

}
