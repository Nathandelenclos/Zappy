/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** Exception.hpp
*/

#pragma once

#include <iostream>
#include <exception>
#include <utility>

/* Defines */

#define USAGE "USAGE: ./zappy_gui -p port -h machine\n\tport\tis the port number\n\tmachine\tis the name of the machine; localhost by default"

#define ARGUMENTS_ERROR "Error: Invalid arguments"

#define PORT_ERROR "Error: Invalid port"

#define MACHINE_ERROR "Error: Invalid machine"

#define TRY "\nTry './zappy_gui -help' for more information."

/* Enum */

enum ExceptionCode {
    Error = -1,
    Usage = 0
};


namespace zappy_gui {

    class Exception : public std::exception {
        public:
            explicit Exception(ExceptionCode exceptionCode, std::string  message) : _exceptionCode(exceptionCode), _message(std::move(message)) {}
            ~Exception() noexcept override = default;

            const char *what() const noexcept override {
                return _message.c_str();
            }

            ExceptionCode getExceptionCode() noexcept {
                return _exceptionCode;
            }

        protected:
        private:
            ExceptionCode _exceptionCode;
            std::string _message;

    };

}
