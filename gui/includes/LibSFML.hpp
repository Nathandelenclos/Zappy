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
            explicit LibSFML();
            ~LibSFML() override;

            void printData();

            void openWindow() override;
            void displayWindow() override;
            void manageEvents() override;

            void loadMap();

            void initGrassOnMap();
            void initResourcesOnMap();

            static sf::Color getRandomColor();

            bool isWindowRunning() const override { return _windowRunning; };

            void setData(const std::shared_ptr<Data>& data) override;

        protected:
            std::shared_ptr<Data> _data;
            bool _windowRunning;
        private:
            sf::RenderWindow _window;
            sf::VideoMode _videoMode;
            sf::Event _event{};
            std::vector<sf::RectangleShape> _cellSquares;
            std::vector<sf::Sprite> _cellSprites;
            sf::Texture _grassTexture;
            std::vector<std::vector<sf::CircleShape>> _circles;

    };

}