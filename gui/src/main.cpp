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
            int maxFd = guiClient->getSocket();
            fd_set readFds;

            std::shared_ptr<zappy_gui::Core> core(new zappy_gui::Core());

            while (guiClient->isRunning()) {
                FD_ZERO(&readFds);
                FD_SET(guiClient->getSocket(), &readFds);

                std::cout << "Waiting for select" << std::endl;
                int readyFds = select(maxFd + 1, &readFds, nullptr, nullptr, nullptr);
                std::cout << "Select done" << std::endl;
                if (readyFds == -1)
                    throw zappy_gui::Exception(Error, "Select failed");
                if (FD_ISSET(guiClient->getSocket(), &readFds)) {
                    core->setData(guiClient->getData());
                }

                core->displayWindow();

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

