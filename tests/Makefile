##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## FreeKOSOVO
##

TESTS	=	toto nested toto_printf

CFLAGS	=	-fno-builtin -O0 -fno-stack-protector
LDFLAGS	=	-Wl,-z,norelro

all: $(TESTS) opt segfault
	$(foreach file, $(TESTS), ./functional_test.sh $(file);)
	./functional_test_options.sh ./opt
	./functional_test_signal.sh ./segfault

fclean:
	rm -f $(TESTS)
	rm -f opt
	rm -f segfault

.PHONY: all fclean
