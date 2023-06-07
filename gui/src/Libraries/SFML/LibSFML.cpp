/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** LibSfml.cpp
*/

#include "LibSFML.hpp"

#include <utility>

namespace zappy_gui {

    LibSFML::LibSFML(Data data) : _data(std::move(data))
    {
        _videoMode.width = WINDOW_WIDTH;
        _videoMode.height = WINDOW_HEIGHT;
        _videoMode.bitsPerPixel = WINDOW_FPS;
        _window.create(_videoMode, WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
        _window.setFramerateLimit(WINDOW_MAX_FPS);
    }

    void LibSFML::displayWindow()
    {
        manageEvents();
        _window.clear(sf::Color::Black);
        _window.display();
    }

    void LibSFML::manageEvents()
    {
        if (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed || _event.key.code == sf::Keyboard::Escape) {
                _window.close();
            }
        }
    }

    extern "C" IGraphical *sfml_entry(Data data)
    {
        return new zappy_gui::LibSFML(std::move(data));
    }

}
