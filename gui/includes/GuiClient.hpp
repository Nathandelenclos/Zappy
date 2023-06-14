/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** GuiClient.hpp
*/

#pragma once

#include "Includes.hpp"

namespace zappy_gui {

    class GuiClient {
        public:
            GuiClient(int port, std::string machine);
            ~GuiClient();

            void connectToServer();
            void sendCommand(const std::string& command) const;

            bool startCommunication();
            bool isRunning();
            void handleUserInput(const std::string& input);

            std::string receiveResponse() const;

            void connectionStatus() const;

            void parseData(const std::string& data);
            static void dataLoading();
            std::shared_ptr<Data> getData() const { return _data; };
            int getSocket() const { return _socket; };

        protected:
            int _port;
            std::string _machine;
        private:
            int _socket;
            int _status;
            std::shared_ptr<Data> _data;
    };

}
