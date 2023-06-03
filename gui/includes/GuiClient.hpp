/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** GuiClient.hpp
*/

#pragma once

#include "Includes.hpp"

namespace zappy_gui {

    struct Data {
        size_t width;
        size_t height;
        size_t frequency;
        std::vector<std::string> teams;
    };

    class GuiClient {
        public:
            GuiClient(int port, std::string machine);
            ~GuiClient();

            void connectToServer();
            void sendCommand(const std::string& command) const;

            void startCommunication();
            void handleUserInput(const std::string& input);

            std::string receiveResponse() const;

            void connectionStatus() const;

            void parseData(const std::string& data);
            static void dataLoading();
            Data getData() const { return _data; };

        protected:
            int _port;
            std::string _machine;
        private:
            int _socket;
            int _status;
            Data _data;
    };

}
