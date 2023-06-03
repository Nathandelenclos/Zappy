/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-david.plouvier
** File description:
** Includes.hpp
*/

#pragma once

/* Libraries */

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <memory>
#include <utility>
#include <sstream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iomanip>

/* Class */

#include "ArgumentsManager.hpp"

                            /* DEFINES */

/* RETURN VALUES */

#define SUCCESS 0
#define FAILURE 84

/* Exceptions */

#define ERROR "Error: "
#define ERROR_SOCKET "socket creation failed"
#define ERROR_INET "invalid address"
#define ERROR_SEND "send failed"
#define ERROR_RECV "failed to receive data from the socket"
#define EXPECTED_WELCOME "Server did not send the expected WELCOME message."

/* Colors */

#define RESET "\033[0m"
#define LIGHTGREEN "\033[32m"
#define LIGHTBLUE "\033[1;36m"
#define RED "\033[0;31m"
#define YELLOW "\033[33m"
#define MAGENTA "\033[0;35m"

/* Messages */

#define AUTHENTICATION "Enter your team name"
#define WELCOME "WELCOME"
#define GRAPHIC "GRAPHIC\n"
#define STATUS "STATUS: "
#define CONNECTED "CONNECTED "
#define DISCONNECTED "DISCONNECTED"
#define PORT "on port "
#define DATA_PARSING "Data parsing in progress"
#define DATA_PARSED "Data parsing completed"
#define LOADING "."

/* Prompts */

#define PROMPT "> "

/* Commands */

#define EXIT "exit"
#define BYE "bye"
#define QUIT "quit"
#define MSZ "msz"
#define SGT "sgt"
#define BCT "bct"
#define TNA "tna"
