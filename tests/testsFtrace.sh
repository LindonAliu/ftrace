#!/bin/bash

# This script is used to test the ftrace functionality of the kernel

# launch ftrace with toto as the trace file
../ftrace ./toto 2>&1 | FileCheck ./ftrace.check

#write in red if is failed and in green if is passed
if [ $? -eq 0 ]; then
    echo -e "\033[32mFtrace passed\033[0m"
else
    echo -e "\033[31mFtrace failed\033[0m"
fi
