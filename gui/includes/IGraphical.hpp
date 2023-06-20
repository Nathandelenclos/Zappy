/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** IGraphical.hpp
*/

#pragma once

#include "Data.hpp"

#define SFML_ENTRY "sfml_entry"
#define RAYLIB_ENTRY "raylib_entry"

class IGraphical {
    public:
        virtual ~IGraphical() = default;
        virtual void updateData(bool updateMap) = 0;
        virtual void openWindow(bool updateMap) = 0;
        virtual void displayWindow() = 0;
        virtual void manageEvents() = 0;
        virtual bool isWindowRunning() const = 0;

        virtual void setData(const std::shared_ptr<zappy_gui::Data>& data) = 0;
};
