/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** Data.hpp
*/

#pragma once

#include <iostream>
#include <vector>
#include <array>

namespace zappy_gui {

    class SegData {
        public:
            std::string winnerTeam;
    };

    class SmgData {
        public:
            std::string message;
    };

    class SgtData {
        public:
            int timeUnit;
    };

    class SstData {
        public:
            int timeUnit;
    };

    class PpoData {
        public:
            int n;
            int x;
            int y;
            int orientation;
    };

    class PlvData {
        public:
            int n;
            int level;
    };

    class PinData {
        public:
            int n;
            int x;
            int y;
            std::array<int, 7> inventory;
    };

    class PexData {
        public:
            int n;
    };

    class PbcData {
        public:
            int n;
            std::string message;
    };

    class PicData {
        public:
            int x;
            int y;
            int level;
            std::vector<int> players;
    };

    class PieData {
        public:
            int x;
            int y;
            int result;
    };

    class PfkData {
        public:
            int n;
    };

    class PdrData {
        public:
            int n;
            int resource;
    };

    class PgtData {
        public:
            int n;
            int resource;
    };

    class PdiData {
        public:
            int n;
    };

    class Players {
        public:
            PpoData playerPos;
            PlvData playerLvl;
            PinData playerInv;
            PexData playerExp;
            PbcData playerBct;
            PicData playerIct;
            PieData playerIet;
            PfkData playerFkt;
            PdrData playerDrt;
            PgtData playerGtt;
            PdiData playerDit;
            int playerTeam;
    };

    class EnwData {
        public:
            int eggId;
            int playerId;
            int x;
            int y;
    };

    class EboData {
        public:
            int eggId;
    };

    class EdiData {
        public:
            int eggId;
    };

    class Egg {
        public:
            EnwData eggNew;
            EboData eggBorn;
            EdiData eggDie;
    };

    class Cell {
        public:
            int x = 0;
            int y = 0;
            std::vector<std::vector<std::vector<int>>> resources;
    };

    class Data {
        public:

            /* Server data */

            int width;
            int height;
            std::vector<std::string> teams;
            int endGame;

            /* Map data */

            std::vector<std::vector<Cell>> grid;
            std::vector<Cell> singleCell;
            std::vector<std::vector<Cell>> map;

            /* Server response */

            std::string messageFromServer;

            /* Players data */

            std::vector<Players> players;

            /* Egg data */

            std::vector<Egg> eggs;

            /* Time unit data */

            SgtData sgtData;
            std::vector<SstData> sstData;

    };

}
