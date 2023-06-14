/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** LibSfml.hpp
*/

#pragma once

#include "Includes.hpp"
#include <SFML/Graphics.hpp>

#define GRASS "./assets/grass.png"

namespace zappy_gui {

    constexpr int CELL_MARGIN = 5;

    class LibSFML : public IGraphical {
        public:
            explicit LibSFML(Data data);
            ~LibSFML() override = default;

            void openWindow() override;
            void displayWindow() override;
            void manageEvents() override;
            void loadMap();

            bool isWindowRunning() const override { return _windowRunning; };

        protected:
            Data _data;
            bool _windowRunning;
        private:
            sf::RenderWindow _window;
            sf::VideoMode _videoMode;
            sf::Event _event{};
            std::vector<sf::RectangleShape> _cellSquares;
            std::vector<sf::Sprite> _cellSprites;
            sf::Texture _grassTexture;
    };

}