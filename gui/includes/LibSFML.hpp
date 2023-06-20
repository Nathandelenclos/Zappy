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
#define WATER_TEXTURE_PATH "./assets/water.png"

namespace zappy_gui {

    constexpr int CELL_MARGIN = 5;

    struct ParticleData {
        sf::RectangleShape particle;
        sf::Vector2f velocity;
        float angle{};
        float angularVelocity{};
        sf::Vector2f acceleration;
    };

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

            void updateParticles(float at);
            void renderParticles(sf::RenderWindow& window);

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
            sf::Texture _waterTexture;
            std::vector<std::vector<sf::CircleShape>> _circles;
            std::map<int, std::vector<ParticleData>> _particles;
    };

}