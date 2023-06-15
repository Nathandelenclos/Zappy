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
        _cellSquares.resize(_data->width * _data->height); // Réserve de l'espace pour tous les carrés
        _circles.resize(_data->width * _data->height);

        if (!_grassTexture.loadFromFile(GRASS))
            throw Exception(Error, "Cannot load grass texture");
        initGrassOnMap();
        initResourcesOnMap();
    }

    void LibSFML::initGrassOnMap()
    {
        // Calculer la taille de chaque carré
        float cellSizeX = static_cast<float>(_window.getSize().x - CELL_MARGIN * (_data->width - 1)) / _data->width;
        float cellSizeY = static_cast<float>(_window.getSize().y - CELL_MARGIN * (_data->height - 1)) / _data->height;

        // Initialiser les carrés
        for (int y = 0; y < _data->height; y++) {
            for (int x = 0; x < _data->width; x++) {
                int index = y * _data->width + x;
                sf::RectangleShape& cellSquare = _cellSquares[index];

                cellSquare.setSize(sf::Vector2f(cellSizeX, cellSizeY));
                // Définir la couleur du carré
                cellSquare.setFillColor(sf::Color::White);

                // Calculer la position du carré centré avec un espacement
                float squarePosX = (cellSizeX + CELL_MARGIN) * x + (_window.getSize().x - (_data->width * (cellSizeX + CELL_MARGIN))) / 2.0f;
                float squarePosY = (cellSizeY + CELL_MARGIN) * y + (_window.getSize().y - (_data->height * (cellSizeY + CELL_MARGIN))) / 2.0f;
                cellSquare.setPosition(squarePosX, squarePosY);

                sf::Sprite sprite;
                sprite.setTexture(_grassTexture);
                sprite.setScale(cellSizeX / sprite.getTextureRect().width, cellSizeY / sprite.getTextureRect().height);
                sprite.setPosition(squarePosX, squarePosY);

                // Ajouter le sprite au conteneur
                _cellSprites.push_back(sprite);
            }
        }
    }

    void LibSFML::initResourcesOnMap()
    {
        // Initialize the circles
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
                float circleRadius = std::min(cellSizeX, cellSizeY) / 6.0f;

                std::uniform_real_distribution<float> dis(-circleRadius / 2.0f, circleRadius / 2.0f);
                std::vector<std::vector<std::vector<int>>>& resources = _data->grid[y][x].resources;

                for (int i = 0; i < 7; i++) {
                    if (!resources[i].empty() && !resources[i][0].empty()) {
                        int resourceQuantity = resources[i][0][0];

                        if (resourceQuantity > 0) {
                            sf::CircleShape circle(circleRadius);

                            float offsetX = dis(gen);
                            float offsetY = dis(gen);
                            circle.setPosition(centerX - circleRadius + offsetX, centerY - circleRadius + offsetY);

                            switch (i) {
                                case 0: // Food
                                    circle.setFillColor(sf::Color::Red);
                                    break;
                                case 1: // Linemate
                                    circle.setFillColor(sf::Color::Green);
                                    break;
                                case 2: // Deraumere
                                    circle.setFillColor(sf::Color::Blue);
                                    break;
                                case 3: // Sibur
                                    circle.setFillColor(sf::Color::Yellow);
                                    break;
                                case 4: // Mendiane
                                    circle.setFillColor(sf::Color(255, 165, 0)); // Orange
                                    break;
                                case 5: // Phiras
                                    circle.setFillColor(sf::Color::Cyan);
                                    break;
                                case 6: // Thystame
                                    circle.setFillColor(sf::Color::Magenta);
                                    break;
                                default:
                                    circle.setFillColor(sf::Color::Transparent);
                                    break;
                            }

                            _circles[index].push_back(circle);
                        }
                    }
                }
            }
        }
    }


    void LibSFML::displayWindow()
    {
        manageEvents();
        _window.clear(sf::Color::Black);
        //Axel: Le menu ici fdp
        loadMap();
        _window.display();
    }

    void LibSFML::manageEvents()
    {
        if (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                _windowRunning = false;
                _window.close();
            }
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
    }

    sf::Color LibSFML::getRandomColor()
    {
        int r = rand() % 256;
        int g = rand() % 256;
        int b = rand() % 256;
        return sf::Color(r, g, b);
    }

    void LibSFML::setData(const std::shared_ptr<Data> &data)
    {
        _data = data;
    }

    void LibSFML::printData()
    {
        std::cout << "Width: " << _data->width << std::endl;
        std::cout << "Height: " << _data->height << std::endl;
        std::cout << "Frequency: " << _data->frequency << std::endl;

        std::cout << "Teams: ";
        for (const std::string& team : _data->teams) {
            std::cout << team << " ";
        }
        std::cout << std::endl;

        std::cout << "Grid: " << std::endl;
        for (const std::vector<Cell>& row : _data->grid) {
            for (const Cell& cell : row) {
                std::cout << "Cell (" << cell.x << ", " << cell.y << "): ";
                std::cout << "Resources: ";
                for (const std::vector<std::vector<int>>& resource : cell.resources) {
                    for (const std::vector<int>& quantity : resource) {
                        for (int value : quantity) {
                            std::cout << value << " ";
                        }
                    }
                }
                std::cout << std::endl;
            }
        }

        std::cout << "Message: " << _data->message << std::endl;
    }


    extern "C" IGraphical *sfml_entry()
    {
        return new zappy_gui::LibSFML();
    }

}
