##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## FreeKOSOVO
##

TESTS	=	toto nested

CFLAGS	=	-fno-builtin

all: $(TESTS) opt segfault
	$(foreach file, $(TESTS), ./functional_test.sh $(file);)
	./functional_test_options.sh ./opt
	./functional_test_signal.sh ./segfault

fclean:
	rm -f $(TESTS)

.PHONY: all fclean
