/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** Parsing.hpp
*/

#pragma once

#include "Includes.hpp"

namespace zappy_gui {

    class Parsing {
        public:
            static void parseMsz(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parseBct(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parseMct(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parseTna(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parsePnw(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parsePpo(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parsePlv(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parsePin(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parsePex(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parsePbc(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parsePic(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parsePie(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parsePfk(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parsePdr(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parsePgt(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parsePdi(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parseEnw(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parseEbo(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parseEdi(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parseSgt(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parseSst(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parseSeg(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parseSmg(std::istringstream& lineStream, const std::shared_ptr<Data>& data);
            static void parseSuc();
            static void parseSbp();
    };

}
