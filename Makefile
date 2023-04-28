##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Make nice stuff
##

SRC		=	main.c		\
			syscall/print.c		\
			syscall/args.c		\
			syscall/syscall.c	\
			syscall/read.c 		\
			nm/collect.c 		\
			nm/load_elf.c 		\
			internal_functions.c       \
			ftrace.c			\
			proc.c				\
			signals.c			\
			return_detection.c

OBJ		=	$(SRC:%.c=obj/%.o)

CFLAGS		+=
CPPFLAGS	+=	-iquote include -Wall -Wextra -D_GNU_SOURCE
LDFLAGS		+=

EXEC		=	ftrace

all:	$(EXEC)

obj/%.o:	src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(EXEC):	$(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	find . -name "*.gcno" -delete
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(EXEC)

re:	fclean all

debug: CFLAGS += -g3
debug: re

.PHONY: all tests_run clean_cov clean fclean re debug
