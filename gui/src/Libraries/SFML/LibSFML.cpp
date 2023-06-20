/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** LibSfml.cpp
*/

#include "LibSFML.hpp"

namespace zappy_gui {

    LibSFML::LibSFML() : _windowRunning(false)
    {
        _menu = true;
        _videoMode.width = WINDOW_WIDTH;
        _videoMode.height = WINDOW_HEIGHT;
        _videoMode.bitsPerPixel = WINDOW_FPS;
        _window.setFramerateLimit(WINDOW_MAX_FPS);
    }

    LibSFML::~LibSFML()
    {
        std::cout << "LibSFML destructor called" << std::endl;
    }

    void LibSFML::openWindow()
    {
        printData();
        _window.create(_videoMode, WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
        _windowRunning = true;
        _cellSquares.resize(_data->width * _data->height);
        _circles.resize(_data->width * _data->height);

        if (!_grassTexture.loadFromFile(GRASS))
            throw Exception(Error, "Cannot load grass texture");
        /*if (!_waterTexture.loadFromFile(WATER_TEXTURE_PATH))
            throw Exception(Error, "Cannot load water texture");*/
        initGrassOnMap();
        initResourcesOnMap();
    }

    void LibSFML::initGrassOnMap()
    {
        float availableWidth = static_cast<float>(_window.getSize().x) - (2 * WINDOW_PADDING);
        float availableHeight = static_cast<float>(_window.getSize().y) - (2 * WINDOW_PADDING);

        float cellSizeX = availableWidth / static_cast<float>(_data->width);
        float cellSizeY = availableHeight / static_cast<float>(_data->height);

        float offsetX = (static_cast<float>(_window.getSize().x) - (static_cast<float>(_data->width) * (cellSizeX + CELL_MARGIN))) / 2.0f;
        float offsetY = (static_cast<float>(_window.getSize().y) - (static_cast<float>(_data->height) * (cellSizeY + CELL_MARGIN))) / 2.0f;

        for (int y = 0; y < _data->height; y++) {
            for (int x = 0; x < _data->width; x++) {
                int index = y * _data->width + x;
                sf::RectangleShape& cellSquare = _cellSquares[index];

                cellSquare.setSize(sf::Vector2f(cellSizeX, cellSizeY));
                cellSquare.setFillColor(sf::Color::White);

                float squarePosX = (cellSizeX + CELL_MARGIN) * static_cast<float>(x) + offsetX;
                float squarePosY = (cellSizeY + CELL_MARGIN) * static_cast<float>(y) + offsetY;
                cellSquare.setPosition(squarePosX, squarePosY);

                sf::Sprite sprite;
                sprite.setTexture(_grassTexture);
                sprite.setScale(cellSizeX / static_cast<float>(sprite.getTextureRect().width), cellSizeY / static_cast<float>(sprite.getTextureRect().height));
                sprite.setPosition(squarePosX, squarePosY);

                _cellSprites.push_back(sprite);
            }
        }
    }

    void LibSFML::initResourcesOnMap()
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        for (int y = 0; y < _data->height; y++) {
            for (int x = 0; x < _data->width; x++) {
                int index = y * _data->width + x;
                sf::RectangleShape& cellSquare = _cellSquares[index];

                float cellSizeX = cellSquare.getSize().x;
                float cellSizeY = cellSquare.getSize().y;
                float centerX = cellSquare.getPosition().x + cellSizeX / 2.0f;
                float centerY = cellSquare.getPosition().y + cellSizeY / 2.0f;
                float particleSize = std::min(cellSizeX, cellSizeY) / 12.0f;

                std::uniform_real_distribution<float> dis(-particleSize / 2.0f, particleSize / 2.0f);
                std::vector<std::vector<std::vector<int>>>& resources = _data->grid[y][x].resources;

                for (int i = 0; i < 7; i++) {
                    if (!resources[i].empty() && !resources[i][0].empty()) {
                        int resourceQuantity = resources[i][0][0];

                        if (resourceQuantity > 0) {
                            sf::RectangleShape particle(sf::Vector2f(particleSize, particleSize));

                            float offsetX = dis(gen);
                            float offsetY = dis(gen);
                            particle.setPosition(centerX - particleSize / 2.0f + offsetX, centerY - particleSize / 2.0f + offsetY);

                            sf::Vector2f velocity(0.0f, 0.0f);
                            float angle = dis(gen) * 360.0f;
                            float angularVelocity = dis(gen) * 90.0f;
                            sf::Vector2f acceleration(0.0f, 9.8f);

                            switch (i) {
                                case 0: // Food
                                    particle.setFillColor(sf::Color::Red);
                                    break;
                                case 1: // Linemate
                                    particle.setFillColor(sf::Color::Green);
                                    break;
                                case 2: // Deraumere
                                    particle.setFillColor(sf::Color::Blue);
                                    break;
                                case 3: // Sibur
                                    particle.setFillColor(sf::Color::Yellow);
                                    break;
                                case 4: // Mendiane
                                    particle.setFillColor(sf::Color(255, 165, 0)); // Orange
                                    break;
                                case 5: // Phiras
                                    particle.setFillColor(sf::Color::Cyan);
                                    break;
                                case 6: // Thystame
                                    particle.setFillColor(sf::Color::Magenta);
                                    break;
                                default:
                                    particle.setFillColor(sf::Color::Transparent);
                                    break;
                            }
                            ParticleData particleData;
                            particleData.particle = particle;
                            particleData.velocity = velocity;
                            particleData.angle = angle;
                            particleData.angularVelocity = angularVelocity;
                            particleData.acceleration = acceleration;
                            _particles[index].push_back(particleData);
                        }
                    }
                }
            }
        }
    }

    void LibSFML::updateParticles(float dt)
    {
        for (auto& particles : _particles) {
            int index = particles.first;
            sf::RectangleShape& cellSquare = _cellSquares[index];
            sf::Vector2f cellSquarePos = cellSquare.getPosition();
            sf::Vector2f cellSquareSize = cellSquare.getSize();

            for (auto& particleData : particles.second) {
                sf::RectangleShape& particle = particleData.particle;
                sf::Vector2f& velocity = particleData.velocity;
                float& angularVelocity = particleData.angularVelocity;
                sf::Vector2f& acceleration = particleData.acceleration;

                sf::Vector2f displacement = velocity * dt + 0.5f * acceleration * dt * dt;
                particle.move(displacement);

                velocity += acceleration * dt;

                float rotation = angularVelocity * dt;
                particle.rotate(rotation);

                sf::Vector2f particlePos = particle.getPosition();
                sf::FloatRect particleBounds = particle.getGlobalBounds();

                if (particlePos.x < cellSquarePos.x || particlePos.x + particleBounds.width > cellSquarePos.x + cellSquareSize.x) {
                    velocity.x *= -1;
                }

                if (particlePos.y < cellSquarePos.y || particlePos.y + particleBounds.height > cellSquarePos.y + cellSquareSize.y) {
                    velocity.y *= -1;
                }
            }
        }
    }


    void LibSFML::displayWindow()
    {
        manageEvents();
        _window.clear(sf::Color::Black);
        if (_menu == false) {
            updateParticles(0.016f);
            loadMap();
        } else
            loadMenu();
        _window.display();
    }

    void LibSFML::loadMenu()
    {
        sf::Texture bouton;
        sf::Texture quit;
        sf::Texture logo;
        _menutext.loadFromFile("assets/menu.jpg");
        bouton.loadFromFile("assets/bouton.png");
        quit.loadFromFile("assets/quit.png");
        logo.loadFromFile("assets/zappy.png");
        sf::Sprite logoPrint(logo);
        sf::Sprite menuPrint(_menutext);
        logoPrint.setScale(1.5, 1.5);
        logoPrint.setPosition(750, 100);
        quitPrint.setTexture(quit);
        boutonPrint.setTexture(bouton);
        quitPrint.setScale(2.8, 1.5);
        quitPrint.setPosition(750, 600);
        boutonPrint.setScale(2.8, 1.5);
        menuPrint.setScale(4, 3);
        boutonPrint.setPosition(750, 400);
        _window.draw(menuPrint);
        _window.draw(logoPrint);
        _window.draw(quitPrint);
        _window.draw(boutonPrint);
    }

    void LibSFML::manageEvents()
    {
        if (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                _windowRunning = false;
                _window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                _menu = false;
            if (_event.type == sf::Event::MouseButtonPressed) {
                if (_event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);
                    if (boutonPrint.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        _menu = false;
                    } if (quitPrint.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        _windowRunning = false;
                        _window.close();
                    }
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && _menu == false)
                printData();
        }
    }

    void LibSFML::loadMap()
    {
        // Dessiner les carrés de la carte
        for (int y = 0; y < _data->height; y++) {
            for (int x = 0; x < _data->width; x++) {
                int index = y * _data->width + x;
                sf::RectangleShape& cellSquare = _cellSquares[index];
                cellSquare.setFillColor(sf::Color::White);

                _window.draw(cellSquare);
                sf::Sprite& cellSprite = _cellSprites[index];
                _window.draw(cellSprite);
                for (const sf::CircleShape& circle : _circles[index]) {
                    _window.draw(circle);
                }
            }
        }
        renderParticles(_window);
    }

    void LibSFML::renderParticles(sf::RenderWindow& window)
    {
        for (const auto& particles : _particles) {
            for (const auto& particleData : particles.second) {
                const sf::RectangleShape& particle = particleData.particle;
                window.draw(particle);
            }
        }
    }

    void LibSFML::setData(const std::shared_ptr<Data> &data)
    {
        _data = data;
    }

    void LibSFML::printData()
    {
        std::cout << "Server data:\n";
        std::cout << "Width: " << _data->width << "\n";
        std::cout << "Height: " << _data->height << "\n";
        if (_data->teams.empty()) {
            std::cout << "No teams data available\n";
        } else {
            std::cout << "Teams:\n";
            for (const auto& team : _data->teams) {
                std::cout << team << "\n";
            }
        }
        std::cout << "End game: " << _data->endGame << "\n";

        std::cout << "Map data:\n";
        if (_data->grid.empty()) {
            std::cout << "No map data available\n";
        } else {
            for (const auto& row : _data->grid) {
                for (const auto& cell : row) {
                    std::cout << "Cell at (" << cell.x << ", " << cell.y << "):\n";
                    if (cell.resources.empty()) {
                        std::cout << "No resources data available\n";
                    } else {
                        std::cout << "Resources:\n";
                        for (const auto& resource : cell.resources) {
                            for (const auto& subResource : resource) {
                                for (const auto& value : subResource) {
                                    std::cout << value << " ";
                                }
                            }
                            std::cout << "\n";
                        }
                    }
                }
            }
        }

        std::cout << "Server response:\n";
        if (_data->messageFromServer.empty()) {
            std::cout << "No message from server available\n";
        } else {
            std::cout << _data->messageFromServer << "\n";
        }

        std::cout << "Players data:\n";
        if (_data->players.empty()) {
            std::cout << "No players data available\n";
        } else {
            for (const auto& player : _data->players) {
                std::cout << "Player ID: " << player.playerPos.n << "\n";
                std::cout << "Player position: (" << player.playerPos.x << ", " << player.playerPos.y << ")\n";
                std::cout << "Player level: " << player.playerLvl.level << "\n";
                std::cout << "Player inventory:\n";
                for (const auto& value : player.playerInv.inventory) {
                    std::cout << value << " ";
                }
                std::cout << "\n";
            }
        }

        std::cout << "Egg data:\n";
        if (_data->eggs.empty()) {
            std::cout << "No eggs data available\n";
        } else {
            for (const auto& egg : _data->eggs) {
                std::cout << "Egg new: (" << egg.eggNew.x << ", " << egg.eggNew.y << ")\n";
                std::cout << "Egg born: " << egg.eggBorn.eggId << "\n";
                std::cout << "Egg die: " << egg.eggDie.eggId << "\n";
            }
        }

        std::cout << "Time unit data:\n";
        std::cout << "SgtData: " << _data->sgtData.timeUnit << "\n";
        if (_data->sstData.empty()) {
            std::cout << "No sstData available\n";
        } else {
            for (const auto& sst : _data->sstData) {
                std::cout << "SstData: " << sst.timeUnit << "\n";
            }
        }
    }


    extern "C" IGraphical *sfml_entry()
    {
        return new zappy_gui::LibSFML();
    }

}
