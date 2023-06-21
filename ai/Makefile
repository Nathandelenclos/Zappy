##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

PROJECT	=	Zappy AI
NAME	=	../zappy_ai

TESTS	=	$(shell find ./tests -type f -name "*.c")

################################################################################

################################################################################

OUTPUT_DOC	=	./doc
INPUT_DOC	=	./src

################################################################################
SHELL	=	/bin/bash
PRINT	=	printf "$(PROJECT):\t" ; printf
RM	=	rm -f
CC	=	chmod 755 zappy_ai

RESET	=	\033[0m
RED	=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
MAGENTA	=	\033[0;35m
CYAN	=	\033[1;36m

################################################################################

all: $(NAME)

debug: $(NAME)

$(NAME):
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Building $(NAME)"
	@ $(CC) && \
	  (printf "$(GREEN)Done$(RESET)\n" ; exit 0) || \
	  (printf "$(RED)Fail$(RESET)\n" ; exit 1)

clean:
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting object files"
	@ printf "$(GREEN)Done$(RESET)\n"

fclean: clean
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting $(NAME)"
	@ $(RM) -r ./doc
	@ printf "$(GREEN)Done$(RESET)\n"

re: fclean all
de: fclean debug