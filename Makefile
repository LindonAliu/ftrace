##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Make nice stuff
##

SRC		=	main.c		\
			print.c		\
			args.c		\
			syscall.c	\
			strace.c	\

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
	$(CC) -o $(EXEC) $(OBJ)

clean:
	find . -name "*.gcno" -delete
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(EXEC)

re:	fclean all

debug: CFLAGS += -g3
debug: re

.PHONY: all tests_run clean_cov clean fclean re debug
