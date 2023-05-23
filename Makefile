##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

PROJECT	=	Zappy
NAME	=	zappy

MAKES	=	./ai	\
            ./gui	\
            ./server	\

################################################################################

SHELL	=	/bin/bash
PRINT	=	printf "$(PROJECT):\t" ; printf
RM	=	rm -f
CC	=	gcc
MAKE	=	make -s -C

RESET	=	\033[0m
RED	=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
MAGENTA	=	\033[0;35m
CYAN	=	\033[1;36m

################################################################################

all: $(NAME)

debug:
	@ $(foreach file, ${MAKES}, ${MAKE} $(file) debug;)

$(NAME):
	@ $(PRINT) "$(YELLOW)%b$(RESET)\n" "Compiling source files"
	@ $(foreach file, ${MAKES}, ${MAKE} $(file);)
	@ $(PRINT) "$(YELLOW)%b$(RESET)\n" "$(GREEN)Done$(RESET)"

clean:
	@ $(foreach file, ${MAKES}, ${MAKE} $(file) clean;)
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting object files"
	@ $(RM) $(OBJS)
	@ printf "$(GREEN)Done$(RESET)\n"

fclean: clean
	@ $(foreach file, ${MAKES}, ${MAKE} $(file) fclean;)
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting $(NAME)"
	@ $(RM) $(NAME)
	@ $(RM) vgcore.*
	@ $(RM) -r ./doc
	@ printf "$(GREEN)Done$(RESET)\n"

tests_run:	$(TESTOBJ)
	@ echo "tests_run"

re: fclean all
de: fclean debug
