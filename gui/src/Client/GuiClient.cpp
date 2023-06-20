/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** GuiClient.cpp
*/

#include "GuiClient.hpp"

namespace zappy_gui {

    GuiClient::GuiClient(int port, std::string machine) : _port(port), _machine(std::move(machine)), _socket(0), _status(0), _updateMap(true) {
        _data = std::make_shared<Data>();
        _parsing = std::make_shared<Parsing>();
        _commands.emplace_back(MSZ);
        _commands.emplace_back(BCT);
        _commands.emplace_back(MCT);
        _commands.emplace_back(TNA);
        _commands.emplace_back(PPO);
        _commands.emplace_back(PLV);
        _commands.emplace_back(PIN);
        _commands.emplace_back(SGT);
        _commands.emplace_back(SST);
    }

    GuiClient::~GuiClient() {
        if (_socket > 0)
            close(_socket);
    }

    void GuiClient::connectToServer() {
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

    void GuiClient::connectionStatus() const {
        if (_status < 0)
            throw Exception(Error, STATUS RED DISCONNECTED RESET);
        else
            std::cout << std::endl << std::endl << STATUS LIGHTGREEN CONNECTED RESET PORT YELLOW << _port << RESET
                      << std::endl << std::endl;
    }

    bool GuiClient::startCommunication() {
        std::string response = receiveResponse();

        if (response.find(WELCOME) != std::string::npos) {
            sendCommand(GRAPHIC);
            std::cout << LIGHTBLUE << response << RESET << AUTHENTICATION << std::endl << std::endl
                      << PROMPT MAGENTA GRAPHIC RESET << std::endl;
            std::cout << (response = receiveResponse()) << std::endl;
            parseDefaultData(response);
            return (true);
        } else {
            std::cout << EXPECTED_WELCOME << std::endl;
            return (false);
        }
    }

    bool GuiClient::analyseResponse() {
        std::string response = receiveResponse();
        if (response.empty() || response == EMPTY)
            return (false);
        std::cout << response << std::endl;
        parseData(response);
        return (true);
    }

    bool GuiClient::isRunning() {
        std::cout << RESET PROMPT MAGENTA;
        std::string userInput;
        std::getline(std::cin, userInput);
        std::cout << RESET;

        if (userInput == EXIT || userInput == QUIT || userInput == BYE)
            return (false);
        handleUserInput(userInput);
        return (true);
    }

    void GuiClient::handleUserInput(const std::string &input) {
        if (input.empty())
            return;
        sendCommand(input + '\n');
        _data->messageFromServer = receiveResponse();
        std::cout << RESET << _data->messageFromServer;
    }

/*    void GuiClient::handleGuiInput()
    {
        for (const auto &command : _commands) {
            if (command == BCT)
                continue;
            else if (command == PPO)
                continue;
            else if (command == PLV)
                continue;
            else if (command == PIN)
                continue;
            else if (command == SGT)
                continue;
            else
                sendCommand(command + '\n');
            analyseResponse();
        }
    }*/

    void GuiClient::sendCommand(const std::string &command) const {
        if (send(_socket, command.c_str(), command.length(), 0) == -1)
            throw Exception(Error, ERROR ERROR_SEND);
    }

    void GuiClient::sendCommand(const std::string &command, const std::string &argument) const {
        std::string fullCommand = command + " " + argument + '\n';
        sendCommand(fullCommand);
    }

    std::string GuiClient::receiveResponse() const
    {
        char buffer[100000] = {0};

        if (read(_socket, buffer, 100000) == -1)
            throw Exception(Error, ERROR ERROR_READ);
        return (buffer);
    }

    void GuiClient::parseDefaultData(const std::string &data) {
        std::istringstream iss(data);
        std::string line;

        while (getline(iss, line)) {
            std::istringstream lineStream(line);
            std::string command;
            lineStream >> command;

            if (command == MSZ) {
                _parsing->parseMsz(lineStream, _data);
            } else if (command == SGT) {
                _parsing->parseSgt(lineStream, _data);
            } else if (command == TNA) {
                _parsing->parseTna(lineStream, _data);
            } else if (command == BCT) {
                _parsing->parseBct(lineStream, _data);
            } else {
                continue;
            }
        }
    }

    void GuiClient::parseData(const std::string &data) {
        _updateMap = false;
        std::istringstream iss(data);
        std::string line;
        getline(iss, line);
        std::istringstream lineStream(line);
        std::string command;
        lineStream >> command;

        if (command == MSZ) {
            _parsing->parseMsz(lineStream, _data);
        } else if (command == BCT) {
            _parsing->parseBct(lineStream, _data);
            _updateMap = true;
        } else if (command == MCT) {
            _parsing->parseMct(lineStream, _data);
            _updateMap = true;
        } else if (command == TNA) {
            _parsing->parseTna(lineStream, _data);
        } else if (command == PNW) {
            _parsing->parsePnw(lineStream, _data);
        } else if (command == PPO) {
            _parsing->parsePpo(lineStream, _data);
        } else if (command == PLV) {
            _parsing->parsePlv(lineStream, _data);
        } else if (command == PIN) {
            _parsing->parsePin(lineStream, _data);
        } else if (command == PEX) {
            _parsing->parsePex(lineStream, _data);
        } else if (command == PBC) {
            _parsing->parsePbc(lineStream, _data);
        } else if (command == PIC) {
            _parsing->parsePic(lineStream, _data);
        } else if (command == PIE) {
            _parsing->parsePie(lineStream, _data);
        } else if (command == PFK) {
            _parsing->parsePfk(lineStream, _data);
        } else if (command == PDR) {
            _parsing->parsePdr(lineStream, _data);
        } else if (command == PGT) {
            _parsing->parsePgt(lineStream, _data);
        } else if (command == PDI) {
            _parsing->parsePdi(lineStream, _data);
        } else if (command == ENW) {
            _parsing->parseEnw(lineStream, _data);
        } else if (command == EBO) {
            _parsing->parseEbo(lineStream, _data);
        } else if (command == EDI) {
            _parsing->parseEdi(lineStream, _data);
        } else if (command == SGT) {
            _parsing->parseSgt(lineStream, _data);
        } else if (command == SST) {
            _parsing->parseSst(lineStream, _data);
        } else if (command == SEG) {
            _parsing->parseSeg(lineStream, _data);
        } else if (command == SMG) {
            _parsing->parseSmg(lineStream, _data);
        } else if (command == SUC) {
            _parsing->parseSuc();
        } else if (command == SBP) {
            _parsing->parseSbp();
        }
    }

    void GuiClient::dataLoading() {
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