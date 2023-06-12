/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** Loader.hpp
*/

#pragma once

#include "Includes.hpp"

namespace zappy_gui {

    template<typename Loader>
    class DLoader {
        public:
            explicit DLoader(const std::string& path) : _handle(dlopen(path.c_str(), RTLD_LAZY))
            {
                if (!_handle)
                    throw Exception(Error, "Cannot load " + path + " library");
            }
            ~DLoader()
            {
                _handle ? dlclose(_handle) : 0;
            }

            std::shared_ptr<Loader> getSFMLInstance(Data *pData)
            {
                std::shared_ptr<IGraphical> lib;
                auto entryPoint = dlsym(_handle, SFML_ENTRY);

                if (!entryPoint)
                    throw Exception(Error, "Cannot load entry point from SFML library");
                auto *(*entry)(Data) = (IGraphical *(*)(Data))entryPoint;
                lib = std::shared_ptr<IGraphical>(entry(*pData));
                if (!lib)
                    throw Exception(Error, "Cannot load SFML library");
                return std::dynamic_pointer_cast<Loader>(lib);
            }

        protected:
        private:
            void *_handle;
    };

    typedef DLoader<IGraphical> GraphicalLoader;
    typedef std::shared_ptr<GraphicalLoader> GraphicalLoaderPtr;

}
