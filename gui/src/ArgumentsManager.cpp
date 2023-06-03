/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** ArgumentsManager.cpp
*/

#include "ArgumentsManager.hpp"

namespace zappy_gui {

    ArgumentsManager::ArgumentsManager(int argc, char **argv) : _ac(argc), _av(argv)
    {
        (_ac == 2) ? _help = _av[1] : _help = "";
    }

    void ArgumentsManager::checkArguments()
    {
        if (_help == "-h" || _help == "-help")
            throw Exception(Usage, USAGE);
        if (_ac != 5)
            throw Exception(Error, ARGUMENTS_ERROR TRY);
        if (std::string(_av[1]) != "-p")
            throw Exception(Error, PORT_ERROR TRY);
        if (std::string(_av[3]) != "-h")
            throw Exception(Error, MACHINE_ERROR TRY);
        _port = std::stoi(_av[2]);
        _machine = _av[4];
    }

}
