##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

PROJECT	=	Zappy Server
NAME	=	../zappy_server

MAIN	= 	src/main.c
SRCS	=	$(shell find ./src -type f -name "*.c" ! -name 'main.c')
HEADS	=	$(shell find ./include -type f -name "*.h")
TESTS	=	$(shell find ./tests -type f -name "*.c")

LIBS	=	./libs/linked_list	\
			./libs/my		\
			./libs/network

OBJS	=	$(SRCS:.c=.o) $(MAIN:.c=.o)

TEST_NAME	=	../../unit_tests

################################################################################

CFLAGS	+=	-W -Wall -Wextra
CFLAGS	+=	-Iinclude/ -I ./libs/

LDFLAGS	+=	-L./libs/
LDFLAGS	+=	-llist
LDFLAGS	+=	-lmy
LDFLAGS	+=	-lnet

TEST_CFLAGS = $(CFLAGS) $(LDFLAGS) --coverage -lcriterion

################################################################################

OUTPUT_DOC	=	./doc
INPUT_DOC	=	./src

################################################################################

SHELL	=	/bin/bash
PRINT	=	printf "$(PROJECT):\t" ; printf
RM	=	rm -f
CC	=	gcc

RESET	=	\033[0m
RED	=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
MAGENTA	=	\033[0;35m
CYAN	=	\033[1;36m

################################################################################

all: $(NAME)

debug: CFLAGS += -g
debug: $(NAME)

buildlib:
	@ $(PRINT) "$(YELLOW)%b$(RESET)\n" "Compiling libs files"
	@ $(foreach lib, ${LIBS}, ${MAKE} -C $(lib);)
	@ $(PRINT) "$(YELLOW)%b$(RESET)\n" "$(GREEN)Done$(RESET)"

$(NAME): buildlib $(OBJS)
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Building $(NAME)"
	@ $(CC) -o $(NAME) $(OBJS) $(LDFLAGS) && \
	  (printf "$(GREEN)Done$(RESET)\n" ; exit 0) || \
	  (printf "$(RED)Fail$(RESET)\n" ; exit 1)

clean:
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting libs files"
	@ $(foreach lib, ${LIBS}, ${MAKE} -C $(lib) clean;)
	@ $(PRINT) "$(YELLOW)%b$(RESET)\n" "$(GREEN)Done$(RESET)"
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting object files"
	@ $(RM) $(OBJS)
	@ printf "$(GREEN)Done$(RESET)\n"

fclean: clean
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting libs files"
	@ $(foreach lib, ${LIBS}, ${MAKE} -C $(lib) fclean;)
	@ $(PRINT) "$(YELLOW)%b$(RESET)\n" "$(GREEN)Done$(RESET)"
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting $(NAME)"
	@ $(RM) $(NAME)
	@ $(RM) vgcore.*
	@ $(RM) -r ./doc
	@ printf "$(GREEN)Done$(RESET)\n"

tests_run:	$(TESTOBJ)
	@ gcc -o $(TEST_NAME) $(TESTS) $(TEST_CFLAGS)
	./$(TESTNAME)
	gcovr --exclude tests/

re: fclean all
de: fclean debug

.c.o:
	@ $(CC) -c $< -o $@ $(CFLAGS) && \
	  ($(PRINT) "  $(GREEN)[OK]$(CYAN)  %b$(RESET)\n" $<) || \
	  ($(PRINT) "  $(RED)[XX]$(CYAN)  %b$(RESET)\n" $< ; exit 1)
