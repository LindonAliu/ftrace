##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## FreeKOSOVO
##

TESTS	=	toto

CFLAGS	=	-fno-builtin

all: $(TESTS)
	$(foreach file, $(TESTS), ./functional_test.sh $(file))

fclean:
	rm -f $(TESTS)

.PHONY: all fclean
