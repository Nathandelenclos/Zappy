##
## EPITECH PROJECT, 2022
## B-CCP-400-LIL-4-1-theplazza-shailendra.blondel
## File description:
## Makefile
##

BINARY = ../zappy_gui

DELTA = $$(echo "$$(tput cols)-47"|bc)
INDEX = 1

CXX = g++

CXXFLAGS = -Wall -Wextra -Werror -std=c++11
DEBUG_FLAGS = -g

SRC_DIR = src/
INCLUDE_DIR = includes/
OBJ_DIR = objs/
SFML_DIR = Libraries/SFML/

SRC = main.cpp \
	  ArgumentsManager.cpp \
	  Data.cpp \
	  Client/GuiClient.cpp \
	  Client/Parsing.cpp \
	  Core/Core.cpp \

SRC_LIST = $(addprefix $(SRC_DIR), $(SRC))
OBJ_LIST = $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))
OBJ_LIST += $(addprefix $(OBJ_DIR), $(SFML_DIR)LibSFML.o)
LIST_SIZE = $(words $(SRC))

all : $(BINARY) libsfml

$(BINARY) : $(OBJ_DIR) $(OBJ_LIST)
	@ cp -r assets/ ..
	@ cp -r libraries/ ..
	@$(CXX) $(OBJ_LIST) -o $(BINARY) \
	    -I $(INCLUDE_DIR) \
	    -L $(SRC_DIR)$(SFML_DIR) -lsfml-graphics -lsfml-window -lsfml-system\
	    $(CXXFLAGS) $(DEBUG_FLAGS)
	@strip -X $@
	@printf "\r\033[48;5;15;38;5;25m✅ MAKE $(BINARY)\033[0m\033[K\n"

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(OBJ_LIST))

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp | $(OBJ_DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(LIST_SIZE)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(LIST_SIZE)))))
	@$(eval COLOR=$(shell echo $$(($(PERCENT)%35+196))))
	@$(eval BAR=$(shell echo $$((20-$(INDEX)*20/$(LIST_SIZE)))))
	@printf "\r\033[38;5;11m⌛ MAKE %10.10s : %2d%% \033[48;5;%dm%*s\033[0m%*s\033[48;5;255m \033[0m \033[38;5;11m %*.*s\033[0m\033[K" $(BINARY) $(PERCENT) $(COLOR) $(DONE) "" $(BAR) "" $(DELTA) $(DELTA) "$@"
	@$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -MMD -c $< -o $@ \
	    -I $(INCLUDE_DIR)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

$(OBJ_DIR)$(SFML_DIR)LibSFML.o: $(SRC_DIR)$(SFML_DIR)LibSFML.cpp | $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -MMD -c $< -o $@ -I $(INCLUDE_DIR) -fPIC

libsfml: $(OBJ_DIR) $(OBJ_DIR)$(SFML_DIR)LibSFML.o
	@$(CXX) -shared -o libraries/LibSFML.so $(OBJ_DIR)$(SFML_DIR)LibSFML.o

clean:
	clear
	@rm -rf $(OBJ_DIR)
	@printf "\r\033[38;5;202m✖ clean $(BINARY)\033[0m\033[K\n"

fclean: clean
	@rm -f $(BINARY)
	@printf "\r\033[38;5;196m❌ fclean $(BINARY)\033[0m\033[K\n"

re: fclean all

.PHONY: all fclean clean re libsfml

-include $(OBJ_LIST:.o=.d)
