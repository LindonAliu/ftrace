##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Make nice stuff
##

SRC_MAIN	=	main.c

SRC			=   syscall/print.c				\
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
				options.c					\
				tail_calls.c

SRC_TESTS	=	tests/is_syscall_test.c		\
				tests/is_internal_function_test.c	\
				tests/is_return_test.c		\
				tests/is_tail_call_test.c

SRC_EXEC	=	$(SRC) $(SRC_MAIN)
SRC_UT		=	$(SRC) $(SRC_TESTS)
SRC_COV		=	$(SRC) $(SRC_MAIN)

OBJ_EXEC	=	$(SRC_EXEC:%.c=obj/%.o)
OBJ_UT		=	$(SRC_UT:%.c=obj/cov/%.o)
OBJ_COV		=	$(SRC_COV:%.c=obj/cov/%.o)

EXEC		=	ftrace
EXEC_UT		=	unit_tests
EXEC_COV	=	tests/ftrace

CFLAGS		+=	-Wall -Wextra
CPPFLAGS	+=	-iquote include -D_GNU_SOURCE
LDFLAGS		+=

COV_FLAGS	=	--coverage -lcriterion

all:	$(EXEC)

obj/%.o:	src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

obj/cov/tests/%.o:	tests/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

obj/cov/%.o:	src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(COV_FLAGS) -c -o $@ $<

$(EXEC):	$(OBJ_EXEC)
	$(CC) -o $(EXEC) $(OBJ_EXEC) $(LDFLAGS)

$(EXEC_UT):	$(OBJ_UT)
	$(CC) -o $(EXEC_UT) $(OBJ_UT) $(LDFLAGS) $(COV_FLAGS)

$(EXEC_COV):	$(OBJ_COV)
	$(CC) -o $(EXEC_COV) $(OBJ_COV) $(LDFLAGS) $(COV_FLAGS)

unit_tests_run: $(EXEC_UT)
	@printf "\033[1;33m -- Running unit tests --\033[0m\n"
	./$(EXEC_UT)

functional_tests_run: $(EXEC_COV)
	$(MAKE) -C tests

tests_run:	$(EXEC) clean $(OBJ_TEST)
	@printf "\033[1;32m -- Running tests --\033[0m\n"
	$(MAKE) unit_tests_run -s
	@printf "\033[1;33m -- Running functionnal tests --\033[0m\n"
	$(MAKE) functional_tests_run
	@printf "\033[1;32m -- Showing coverage --\033[0m\n"
	gcovr --exclude tests
	gcovr --branches --exclude tests

clean:
	find . -name "*.gcno" -delete
	find . -name "*.gcda" -delete
	$(RM) $(OBJ_EXEC) $(OBJ_UT) $(OBJ_COV)

fclean: clean
	$(RM) $(EXEC) $(EXEC_UT) $(EXEC_COV)
	$(MAKE) fclean -C tests

.NOTPARALLEL: re
re:	fclean all

debug: CFLAGS += -g3
debug: re

.PHONY: all tests_run clean fclean re debug
.PHONY: functional_tests_run unit_tests_run
