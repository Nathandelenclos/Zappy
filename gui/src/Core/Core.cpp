/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** Core.cpp
*/

#include "Core.hpp"

namespace zappy_gui {

    Core::Core()
    {
        findLibraries();
        for (const auto& lib : _libraries) {
            if (lib == "./libraries/LibSFML.so")
                _loader = std::make_shared<GraphicalLoader>(lib);
        }
        _isRunning = true;
    }

    Core::~Core()
    {
        if (_lib)
            _lib.reset();
        if (_loader)
            _loader.reset();
        std::cout << "Core destroyed" << std::endl;
    }

    void Core::findLibraries()
    {
        _libraries.clear();

        DIR *dir;
        struct dirent *entry;
        const std::string libPath = LIB_PATH;

        if ((dir = opendir(libPath.c_str())) != nullptr) {
            while ((entry = readdir(dir)) != nullptr) {
                const std::string filename = entry->d_name;
                if (filename.length() > 3 && filename.substr(filename.length() - 3) == ".so")
                    _libraries.push_back(libPath + filename);
            }
        }
        closedir(dir);
    }

    void Core::setData(const std::shared_ptr<Data>& data)
    {
        _data = data;
    }

    void Core::createWindow()
    {
        _lib = _loader->getSFMLInstance();
        _lib->setData(_data);
        _lib->openWindow();
    }

    void Core::displayWindow()
    {
        _lib->setData(_data);
        _lib->displayWindow();
        if (!_lib->isWindowRunning())
            _isRunning = false;
    }

}
