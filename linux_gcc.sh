#!/bin/bash

RELEASE=false

# Preprocessor
WARNINGS="-Wno-unused-but-set-variable -Wno-sign-compare -Wno-missing-field-initializers -Wno-switch"

FILES=""preprocessor/main.cpp" "preprocessor/utils.cpp" "preprocessor/lexer.cpp" "preprocessor/platform.cpp" "preprocessor/write_file.cpp""

echo "Building preprocessor"
if [ "$RELEASE" = "true" ]; then
    g++ -Wall -Wextra $FILES -std=c++11 -fno-exceptions -fno-rtti -o preprocessor_exe -DERROR_LOGGING=0 -DRUN_TESTS=0 -DINTERNAL=0 -DMEM_CHECK=0 -DWIN32=0 -DLINUX=1 $WARNINGS -g -ldl
else
    g++ -Wall -Wextra $FILES "preprocessor/test.cpp" "preprocessor/google_test/gtest-all.cc" -fno-exceptions -fno-rtti -o preprocessor_exe -DERROR_LOGGING=1 -DRUN_TESTS=1 -DINTERNAL=1 -DMEM_CHECK=1 -DWIN32=0 -DLINUX=1 $WARNINGS -g -ldl -pthread
fi
mv "./preprocessor_exe" "build/preprocessor"

# Run test code after building.
if [ "$GTEST" = "true" ]; then
    if [ "$RELEASE" = "true" ]; then
        echo "Running Preprocessor tests"
        ./build/preprocessor -t
    fi
fi
