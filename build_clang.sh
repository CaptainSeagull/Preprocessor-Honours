#!/bin/bash

RELEASE=false
GTEST=false
BUILD_TEST_CODE=true
BUILD_BREAKOUT=true

# Preprocessor
WARNINGS="-Wno-unused-function -Wno-unused-variable -Wno-c++11-compat-deprecated-writable-strings -Wno-switch -Wno-sign-compare -Wno-unused-parameter -Wno-writable-strings -Wno-unknown-escape-sequence"

FILES=""preprocessor/main.cpp" "preprocessor/utils.cpp" "preprocessor/lexer.cpp" "preprocessor/platform_linux.cpp""

echo "Building preprocessor"
if [ "$RELEASE" = "true" ]; then
    clang++-3.8 -Wall -Wextra $FILES -std=c++98 -fno-exceptions -fno-rtti -o preprocessor_exe -DERROR_LOGGING=0 -DRUN_TESTS=0 -DINTERNAL=0 -DMEM_CHECK=0 -DWIN32=0 -DLINUX=1 $WARNINGS -g -ldl
else
    if [ "$GTEST" = "false" ]; then
        clang++-3.8 -Wall -Wextra $FILES -std=c++98 -fno-exceptions -fno-rtti -o preprocessor_exe -DERROR_LOGGING=1 -DRUN_TESTS=0 -DINTERNAL=1 -DMEM_CHECK=1 -DWIN32=0 -DLINUX=1 $WARNINGS -g -ldl
    else
        clang++-3.8 -Wall -Wextra $FILES "preprocessor/test.cpp" "preprocessor/google_test/gtest-all.cc" -std=c++98 -fno-exceptions -fno-rtti -o preprocessor_exe -DERROR_LOGGING=1 -DRUN_TESTS=1 -DINTERNAL=1 -DMEM_CHECK=1 -DWIN32=0 -DLINUX=1 $WARNINGS -g -ldl -pthread
    fi
fi
mv "./preprocessor_exe" "build/preprocessor"

# Run code after building.
if [ "$GTEST" = "true" ]; then
    if [ "$RELEASE" = "false" ]; then      
        echo "Running Preprocessor tests"
        ./build/preprocessor -t
    fi
fi

# Test.
if [ "$BUILD_TEST_CODE" = "true" ]; then
    echo "Building test code"
    pushd "test"
    "../build/preprocessor" test_code.cpp
    popd

    clang++-3.8 -Wall -Wextra "test/test_code.cpp" -std=c++11 -o test_exe -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-c++11-compat-deprecated-writable-strings -g -ldl
    mv "./test_exe" "build/test"
fi

# Breakout.
if [ "$BUILD_BREAKOUT" = "true" ]; then
    echo "Building Breakout."
    pushd "test"
    "../build/preprocessor" test_code.cpp
    popd

    clang++-3.8 -Wall -Wextra "breakout/breakout.cpp" -std=c++11 -o breakout_exe -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-c++11-compat-deprecated-writable-strings -g -ldl -lSDL2
    mv "./breakout_exe" "build/breakout"
fi
