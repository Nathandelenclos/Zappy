/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** main.cpp
*/

#include "Includes.hpp"
#include "GuiClient.hpp"

int main(int argc, char **argv)
{
    std::shared_ptr<zappy_gui::ArgumentsManager> argumentsManager(new zappy_gui::ArgumentsManager(argc, argv));

    try {
        argumentsManager->checkArguments();
        std::shared_ptr<zappy_gui::GuiClient> guiClient(new zappy_gui::GuiClient(argumentsManager->getPort(), argumentsManager->getMachine()));
        guiClient->connectToServer();
        guiClient->startCommunication();
        std::cout << guiClient->getData().width << std::endl;
        std::cout << guiClient->getData().height << std::endl;
        std::cout << guiClient->getData().frequency << std::endl;
        for (auto &team : guiClient->getData().teams)
            std::cout << team << std::endl;
    } catch (zappy_gui::Exception &e) {
        if (e.getExceptionCode() == Usage) {
            std::cout << e.what() << std::endl;
            return (SUCCESS);
        } else if (e.getExceptionCode() == Error) {
            std::cerr << e.what() << std::endl;
            return (FAILURE);
        }
    }

    return (SUCCESS);
}

