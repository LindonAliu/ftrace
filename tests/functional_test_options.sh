#!/usr/bin/env bash
##
## EPITECH PROJECT, 2023
## functional_test_options
## File description:
## FreeKOSOVO
##

# launch ftrace with toto as the trace file
./ftrace 2>&1 | FileCheck ./opt_error.check

if [ $? -eq 0 ]; then
    echo -e "No args: \033[32mTest passed\033[0m"
else
    echo -e "No args: \033[31mTest failed\033[0m"
fi

./ftrace -z 2>&1 | FileCheck ./opt_error2.check

if [ $? -eq 0 ]; then
    echo -e "Invalid opt: \033[32mTest passed\033[0m"
else
    echo -e "Invalid opt: \033[31mTest failed\033[0m"
fi

./ftrace -n -s ./$1 2>&1 | FileCheck ./$1.check

if [ $? -eq 0 ]; then
    echo -e "Invalid opt2: \033[32mTest passed\033[0m"
else
    echo -e "Invalid opt2: \033[31mTest failed\033[0m"
fi

./ftrace -s ./$1 2>&1 | FileCheck ./$1.check

if [ $? -eq 0 ]; then
    echo -e "-s opt: \033[32mTest passed\033[0m"
else
    echo -e "-s opt: \033[31mTest failed\033[0m"
fi

./ftrace -i ./$1 2>&1 | FileCheck ./$1.check

if [ $? -eq 0 ]; then
    echo -e "-i opt: \033[32mTest passed\033[0m"
else
    echo -e "-i opt: \033[31mTest failed\033[0m"
fi

./ftrace ls 2> /dev/null > /dev/null

if [ $? -eq 0 ]; then
    echo -e "ls: \033[32mTest passed\033[0m"
else
    echo -e "ls: \033[31mTest failed\033[0m"
fi
