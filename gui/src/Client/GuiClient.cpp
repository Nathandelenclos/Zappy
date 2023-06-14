/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** GuiClient.cpp
*/

#include "GuiClient.hpp"

namespace zappy_gui {

    GuiClient::GuiClient(int port, std::string machine) : _port(port), _machine(std::move(machine)), _socket(0), _status(0)
    {
    }

    GuiClient::~GuiClient()
    {
        if (_socket > 0)
            close(_socket);
    }

    void GuiClient::connectToServer()
    {
        _socket = socket(AF_INET, SOCK_STREAM, 0);
        if (_socket == -1)
            throw Exception(Error, ERROR ERROR_SOCKET);
        sockaddr_in serverAddress{};
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(_port);

        if (inet_pton(AF_INET, _machine.c_str(), &serverAddress.sin_addr) <= 0)
            throw Exception(Error, ERROR ERROR_INET);
        _status = connect(_socket, reinterpret_cast<struct sockaddr *>(&serverAddress), sizeof(serverAddress));
        connectionStatus();
    }

    void GuiClient::connectionStatus() const
    {
        if (_status < 0)
            throw Exception(Error, STATUS RED DISCONNECTED RESET);
        else
            std::cout << std::endl << std::endl << STATUS LIGHTGREEN CONNECTED RESET PORT YELLOW << _port << RESET << std::endl << std::endl;
    }

    bool GuiClient::startCommunication()
    {
        std::string response = receiveResponse();

        if (response.find(WELCOME) != std::string::npos) {
            sendCommand(GRAPHIC);
            std::cout << LIGHTBLUE << response << RESET << AUTHENTICATION << std::endl << std::endl << PROMPT MAGENTA GRAPHIC RESET << std::endl;
            std::cout << (response = receiveResponse()) << std::endl;
            parseData(response);
            return (true);
        } else {
            std::cout << EXPECTED_WELCOME << std::endl;
            return (false);
        }
    }

    bool GuiClient::isRunning()
    {
        std::cout << RESET PROMPT MAGENTA;
        std::string userInput;
        std::getline(std::cin, userInput);
        std::cout << RESET;

        if (userInput == EXIT || userInput == QUIT || userInput == BYE)
            return (false);
        handleUserInput(userInput);
        return (true);
    }

    void GuiClient::handleUserInput(const std::string &input)
    {
        if (input.empty())
            return;
        sendCommand(input + '\n');
        _data->message = receiveResponse();
        std::cout << RESET << _data->message;
    }

    void GuiClient::sendCommand(const std::string &command) const
    {
        if (send(_socket, command.c_str(), command.length(), 0) == -1)
            throw Exception(Error, ERROR ERROR_SEND);
    }

    std::string GuiClient::receiveResponse() const
    {
        const int bufferSize = 100000;
        char buffer[bufferSize];
        memset(buffer, 0, sizeof(buffer));

        int bytesRead = recv(_socket, buffer, bufferSize - 1, 0);
        if (bytesRead == -1)
            throw Exception(Error, ERROR ERROR_RECV);

        std::string response(buffer);
        return response;
    }

    void GuiClient::parseData(const std::string &data)
    {
        /* dataLoading(); */
        _data = std::make_shared<Data>();
        std::istringstream iss(data);
        std::string line;

        while (getline(iss, line)) {
            std::istringstream lineStream(line);
            std::string command;
            lineStream >> command;

            if (command == MSZ) {
                lineStream >> _data->width >> _data->height;
                _data->grid.resize(_data->width, std::vector<Cell>(_data->height));
            } else if (command == SGT) {
                lineStream >> _data->frequency;
            } else if (command == TNA) {
                std::string teamName;
                lineStream >> teamName;
                _data->teams.push_back(teamName);
            } else if (command == BCT) {
                int x, y;
                lineStream >> x >> y;

                if (x >= 0 && x < _data->width && y >= 0 && y < _data->height) {
                    Cell& cell = _data->grid[x][y];
                    std::vector<int> resources;
                    int resource;

                    while (lineStream >> resource)
                        resources.push_back(resource);
                    cell.x = x;
                    cell.y = y;
                    cell.resources = resources;
                }
            } else
                continue;
        }
    }

    void GuiClient::dataLoading()
    {
        std::cout << LIGHTBLUE DATA_PARSING;
        std::cout.flush();
        sleep(1);
        for (int i = 0; i < 3; ++i) {
            std::cout << LOADING;
            std::cout.flush();
            sleep(1);
        }
        std::cout << std::endl;
        std::cout << LIGHTGREEN DATA_PARSED RESET << std::endl << std::endl;
    }

}