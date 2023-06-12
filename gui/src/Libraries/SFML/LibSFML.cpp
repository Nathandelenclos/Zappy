/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** LibSfml.cpp
*/

#include "LibSFML.hpp"

#include <utility>

namespace zappy_gui {

    LibSFML::LibSFML(Data data) : _data(std::move(data)), _windowRunning(false)
    {
        _videoMode.width = WINDOW_WIDTH;
        _videoMode.height = WINDOW_HEIGHT;
        _videoMode.bitsPerPixel = WINDOW_FPS;
        _window.setFramerateLimit(WINDOW_MAX_FPS);
    }

    void LibSFML::openWindow()
    {
        _window.create(_videoMode, WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
        _windowRunning = true;
    }

    void LibSFML::displayWindow()
    {
        manageEvents();
        loadMap();
        _window.clear(sf::Color::Black);
        _window.display();
    }

    void LibSFML::manageEvents()
    {
        if (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed || _event.key.code == sf::Keyboard::Escape) {
                _windowRunning = false;
                _window.close();
            }
        }
    }

    void LibSFML::loadMap()
    {
        std::cout << "LOADING MAP" << std::endl;
        for (int y = 0; y < _data.height; y++) {
            for (int x = 0; x < _data.width; x++) {
                const Cell& cell = _data.grid[x][y];
                std::cout << "Cell(" << x << ", " << y << "): ";
                for (int resource : cell.resources) {
                    std::cout << resource << " ";
                }
                std::cout << std::endl;
            }
        }
    }

    extern "C" IGraphical *sfml_entry(Data data)
    {
        return new zappy_gui::LibSFML(std::move(data));
    }

}
