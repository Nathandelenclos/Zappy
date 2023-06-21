/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** Parsing.cpp
*/

#include "Parsing.hpp"

namespace zappy_gui {

    void Parsing::parseMsz(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        int width, height;
        lineStream >> width >> height;
        data->width = width;
        data->height = height;
        if (data->width != data->height)
            throw Exception(Error, "Map must be a square");
        data->grid.resize(data->width, std::vector<Cell>(data->height));
    }

    void Parsing::parseBct(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        int x;
        int y;
        lineStream >> x >> y;

        if (x >= 0 && x < data->width && y >= 0 && y < data->height) {
            Cell& cell = data->grid[x][y];
            std::vector<std::vector<std::vector<int>>>& resources = cell.resources;
            resources.resize(7, std::vector<std::vector<int>>(1, std::vector<int>(1)));

            for (int i = 0; i < 7; i++) {
                int resource;
                lineStream >> resource;
                resources[i][0][0] = resource;
            }

            cell.x = x;
            cell.y = y;
        }
    }

    void Parsing::parseMct(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        int numTiles;
        lineStream >> numTiles;

        for (int i = 0; i < numTiles; i++) {
            int x;
            int y;
            lineStream >> x >> y;

            if (x >= 0 && x < data->width && y >= 0 && y < data->height) {
                Cell& cell = data->grid[x][y];
                std::vector<std::vector<std::vector<int>>>& resources = cell.resources;
                resources.resize(7, std::vector<std::vector<int>>(1, std::vector<int>(1)));

                for (int j = 0; j < 7; j++) {
                    int resource;
                    lineStream >> resource;
                    resources[j][0][0] = resource;
                }

                cell.x = x;
                cell.y = y;
            }
        }
    }

    void Parsing::parseTna(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        std::string teams;
        lineStream >> teams;
        data->teams.push_back(teams);
    }

    void Parsing::parsePnw(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        int n;
        int x;
        int y;
        int orientation;
        int level;
        std::string teamName;
        lineStream >> n >> x >> y >> orientation >> level >> teamName;
        Players playerData;
        playerData.playerPos = {n, x, y, orientation};
        playerData.playerLvl = {n, level};
        playerData.playerTeam = teamName;
        data->players.push_back(playerData);
        std::cout << "Player " << n << " joined the game" << std::endl;
    }

    void Parsing::parsePpo(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        PpoData ppoData{};
        lineStream >> ppoData.n >> ppoData.x >> ppoData.y >> ppoData.orientation;
        Players playerData;
        playerData.playerPos = ppoData;
        data->players.push_back(playerData);
    }

    void Parsing::parsePlv(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        PlvData plvData{};
        lineStream >> plvData.n >> plvData.level;
        Players playerData;
        playerData.playerLvl = plvData;
        data->players.push_back(playerData);
    }

    void Parsing::parsePin(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        PinData pinData{};
        lineStream >> pinData.n >> pinData.x >> pinData.y;
        for (int i = 0; i < 7; i++) {
            int resource;
            lineStream >> resource;
            pinData.inventory[i] = resource;
        }
        Players playerData;
        playerData.playerInv = pinData;
        data->players.push_back(playerData);
    }

    void Parsing::parsePex(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        PexData pexData{};
        lineStream >> pexData.n;
        Players playerData;
        playerData.playerExp = pexData;
        data->players.push_back(playerData);
    }

    void Parsing::parsePbc(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        PbcData pbcData{};
        lineStream >> pbcData.n >> pbcData.message;
        Players playerData;
        playerData.playerBct = pbcData;
        data->players.push_back(playerData);
    }

    void Parsing::parsePic(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        PicData picData{};
        lineStream >> picData.x >> picData.y >> picData.level;
        for (int i = 0; i < picData.level; i++) {
            int n;
            lineStream >> n;
            picData.players.push_back(n);
        }
        Players playerData;
        playerData.playerIct = picData;
        data->players.push_back(playerData);
    }

    void Parsing::parsePie(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        PieData pieData{};
        lineStream >> pieData.x >> pieData.y >> pieData.result;
        Players playerData;
        playerData.playerIet = pieData;
        data->players.push_back(playerData);
    }

    void Parsing::parsePfk(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        PfkData pfkData{};
        lineStream >> pfkData.n;
        Players playerData;
        playerData.playerFkt = pfkData;
        data->players.push_back(playerData);
    }

    void Parsing::parsePdr(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        PdrData pdrData{};
        lineStream >> pdrData.n >> pdrData.resource;
        Players playerData;
        playerData.playerDrt = pdrData;
        data->players.push_back(playerData);
    }

    void Parsing::parsePgt(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        PgtData pgtData{};
        lineStream >> pgtData.n >> pgtData.resource;
        Players playerData;
        playerData.playerGtt = pgtData;
        data->players.push_back(playerData);
    }

    void Parsing::parsePdi(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        PdiData pdiData{};
        lineStream >> pdiData.n;
        Players playerData;
        playerData.playerDit = pdiData;
        data->players.push_back(playerData);
    }

    void Parsing::parseEnw(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        EnwData enwData{};
        lineStream >> enwData.eggId >> enwData.playerId >> enwData.x >> enwData.y;
        Egg eggData;
        eggData.eggNew = enwData;
        data->eggs.push_back(eggData);
    }

    void Parsing::parseEbo(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        EboData eboData{};
        lineStream >> eboData.eggId;
        Egg eggData;
        eggData.eggBorn = eboData;
        data->eggs.push_back(eggData);
    }

    void Parsing::parseEdi(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        EdiData ediData{};
        lineStream >> ediData.eggId;
        Egg eggData;
        eggData.eggDie = ediData;
        data->eggs.push_back(eggData);
    }

    void Parsing::parseSgt(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        int timeUnit;
        lineStream >> timeUnit;
        data->sgtData.timeUnit = timeUnit;
    }

    void Parsing::parseSst(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        int timeUnit;
        lineStream >> timeUnit;
        SstData sstData{};
        sstData.timeUnit = timeUnit;
        data->sstData.push_back(sstData);
    }

    void Parsing::parseSeg(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        lineStream >> data->endGame;
    }

    void Parsing::parseSmg(std::istringstream& lineStream, const std::shared_ptr<Data>& data)
    {
        lineStream >> data->messageFromServer;
    }

    void Parsing::parseSuc()
    {
        std::cout << "Unknown command" << std::endl;
    }

    void Parsing::parseSbp()
    {
        std::cout << "Command parameter" << std::endl;
    }

}