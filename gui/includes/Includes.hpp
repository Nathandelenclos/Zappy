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
#include <dlfcn.h>
#include <dirent.h>
#include <fcntl.h>
#include <utility>
#include <unordered_map>

#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iomanip>
#include <random>
#include <thread>

/* Class */

#include "IGraphical.hpp"
#include "ArgumentsManager.hpp"
#include "Data.hpp"

                            /* DEFINES */

/* RETURN VALUES */

#define SUCCESS 0
#define FAILURE 84

/* Exceptions */

#define ERROR "Error: "
#define ERROR_SOCKET "socket creation failed"
#define ERROR_INET "invalid address"
#define ERROR_SEND "send failed"
#define ERROR_READ "failed to receive data from the socket"
#define EXPECTED_WELCOME "Server did not send the expected WELCOME message."

/* Path to libraries */

#define LIB_PATH "./libraries/"

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
#define EMPTY "\n"

#define MSZ "msz"
#define BCT "bct"
#define MCT "mct"
#define TNA "tna"
#define PNW "pnw"
#define PPO "ppo"
#define PLV "plv"
#define PIN "pin"
#define PEX "pex"
#define PBC "pbc"
#define PIC "pic"
#define PIE "pie"
#define PFK "pfk"
#define PDR "pdr"
#define PGT "pgt"
#define PDI "pdi"
#define ENW "enw"
#define EBO "ebo"
#define EDI "edi"
#define SGT "sgt"
#define SST "sst"
#define SEG "seg"
#define SMG "smg"
#define SUC "suc"
#define SBP "sbp"


/* SFML */

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WINDOW_FPS 60
#define WINDOW_MAX_FPS 144
#define WINDOW_TITLE "Zappy"
#define WINDOW_PADDING 100

/* Enum */

