#!/usr/bin/env bash
##
## EPITECH PROJECT, 2023
## ftrace
## File description:
## functional test script
##

# launch ftrace with toto as the trace file
./ftrace ./toto 2>&1 | FileCheck ./toto.check

#write in red if is failed and in green if is passed
if [ $? -eq 0 ]; then
    echo -e "\033[32mTest passed\033[0m"
else
    echo -e "\033[31mTest failed\033[0m"
fi
