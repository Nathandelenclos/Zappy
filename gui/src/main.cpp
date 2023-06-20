/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** main.cpp
*/

#include "GuiClient.hpp"
#include "Core.hpp"

int main(int argc, char **argv)
{
    std::shared_ptr<zappy_gui::ArgumentsManager> argumentsManager(new zappy_gui::ArgumentsManager(argc, argv));

    try {
        argumentsManager->checkArguments();
        std::shared_ptr<zappy_gui::GuiClient> guiClient(new zappy_gui::GuiClient(argumentsManager->getPort(), argumentsManager->getMachine()));
        guiClient->connectToServer();
        if (guiClient->startCommunication()) {
            //guiClient->isRunning();
            int v_select = 0;
            fd_set readFds;

            std::shared_ptr<zappy_gui::Core> core(new zappy_gui::Core());
            core->setData(guiClient->getData());
            core->createWindow();
            struct timeval timeout = {0, 0};

            while (core->isRunning()) {
                FD_ZERO(&readFds);
                FD_SET(guiClient->getSocket(), &readFds);
                timeout.tv_usec = 1;

                v_select = select(guiClient->getSocket() + 1, &readFds, nullptr, nullptr, &timeout);
                if (v_select == -1)
                    throw zappy_gui::Exception(Error, "Select failed");
                core->displayWindow();
                if (FD_ISSET(guiClient->getSocket(), &readFds)) {
                    guiClient->analyseResponse();
                    core->setData(guiClient->getData());
                }
            }
        } else {
            guiClient->connectionStatus();
        }
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

