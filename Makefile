##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Make nice stuff
##

SRC_NT		=	main.c

SRC_ALL		=   syscall/print.c				\
				syscall/args.c				\
				syscall/syscall.c			\
				syscall/read.c 				\
				nm/collect.c 				\
				nm/load_elf.c 				\
				internal_functions.c      	\
				ftrace.c					\
				proc.c						\
				signals.c					\
				return_detection.c			\
				tail_calls.c

SRC_TEST	=

SRC_EXEC	=	$(SRC_ALL) $(SRC_NT)
OBJ_EXEC	=	$(SRC_EXEC:%.c=obj/%.o)
OBJ_TEST	=	$(SRC_TEST:%.c=obj/tests/%.o) $(SRC_ALL:%.c=obj/tests/src/%.o)

CFLAGS		+=
CPPFLAGS	+=	-iquote include -Wall -Wextra -D_GNU_SOURCE
LDFLAGS		+=

EXEC		=	ftrace
EXEC_TEST	=	unit_tests

all:	$(EXEC)

obj/%.o:	src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

obj/tests/tests/%.o:	tests/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

obj/tests/src/%.o:	CPPFLAGS += --coverage
obj/tests/src/%.o:	src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(EXEC):	$(OBJ_EXEC)
	$(CC) -o $(EXEC) $(OBJ_EXEC) $(LDFLAGS)

unit_tests_run: LDFLAGS += -lcriterion --coverage
unit_tests_run: $(EXEC) clean $(OBJ_TEST)
	@printf "\033[1;33m -- Running unit tests --\033[0m\n"
	$(CC) -o $(EXEC_TEST) $(OBJ_TEST) $(LDFLAGS)
	./$(EXEC_TEST)
	gcovr --exclude tests
	gcovr --branches --exclude tests

functionnal_tests_run:
	@make -C tests -s

tests_run:	$(EXEC) clean $(OBJ_TEST)
	@printf "\033[1;32m -- Running tests --\033[0m\n"
	@make unit_tests_run -s
	@printf "\033[1;33m -- Running functionnal tests --\033[0m\n"
	@make functionnal_tests_run

clean:
	find . -name "*.gcno" -delete
	$(RM) $(EXEC_TEST)
	-$(RM) -r obj

fclean: clean
	$(RM) $(EXEC)
	make fclean -C tests

re:	fclean all

debug: CFLAGS += -g3
debug: re

.PHONY: all tests_run clean_cov clean fclean re debug
