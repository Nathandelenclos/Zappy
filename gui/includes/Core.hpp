/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** Core.hpp
*/

#pragma once

#include "Includes.hpp"
#include "Doader.hpp"

namespace zappy_gui {

    class Core {
        public:
            Core();
            ~Core();

            bool isRunning() const { return _isRunning; };
            bool needUpdate() const { return _needUpdate; };

            void findLibraries();
            void setData(const std::shared_ptr<Data>& data, bool update, bool updateMap);

            void createWindow();
            void displayWindow();

        protected:
            bool _needUpdate;
            bool _isRunning;
            std::vector<std::string> _libraries;
            std::shared_ptr<Data> _data;
        private:
            std::shared_ptr<IGraphical> _lib;
            bool _updateMap;
            GraphicalLoaderPtr _loader;
    };

}
