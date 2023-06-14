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
        _window.create(_videoMode, WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
        _windowRunning = true;
        _cellSquares.resize(_data->width * _data->height); // Réserve de l'espace pour tous les carrés

        if (!_grassTexture.loadFromFile(GRASS))
            throw Exception(Error, "Cannot load grass texture");

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

                // ...
                // Mettre à jour les propriétés des carrés (couleur, ressources, etc.)
                // ...

                _window.draw(cellSquare);
                sf::Sprite& cellSprite = _cellSprites[index];
                _window.draw(cellSprite);
            }
        }
    }

    void LibSFML::setData(const std::shared_ptr<Data> &data)
    {
        _data = data;
    }

    extern "C" IGraphical *sfml_entry()
    {
        return new zappy_gui::LibSFML();
    }

}
