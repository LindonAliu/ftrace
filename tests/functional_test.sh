#!/usr/bin/env bash
##
## EPITECH PROJECT, 2023
## ftrace
## File description:
## functional test script
##

# launch ftrace with toto as the trace file
./ftrace ./$1 2>&1 | FileCheck ./$1.check

if [ $? -eq 0 ]; then
    echo -e "$1: \033[32mTest passed\033[0m"
else
    echo -e "$1: \033[31mTest failed\033[0m"
fi
