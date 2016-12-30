#!/bin/bash
# Batch File to compile the preprocessor on Linux.

RELEASE=false
GTEST=false
RUN_TEST_CODE=true
RUN_GCC_FOR_EXTRA_TEST=false

# Preprocessor
WARNING_LEVEL="-Wall -Wextra"
WARNINGS="-Wno-unused-function -Wno-unused-variable -Wno-c++11-compat-deprecated-writable-strings -Wno-switch -Wno-sign-compare -Wno-unused-parameter"
CPP_VERSION="-std=c++98"
DISABLED="-fno-exceptions -fno-rtti"
OUTPUT_NAME="preprocessor_exe"
DEFINES="-DWIN32=0 -DLINUX=1"

if [ "$RELEASE"=="true" ]; then
    clang++-3.8 $WARNING_LEVEL "preprocessor/preprocessor.cpp" $CPP_VERSION $DISABLED -o $OUTPUT_NAME -DERROR_LOGGING=0 -DRUN_TESTS=0 -DINTERNAL=0 -DMEM_CHECK=0 $DEFINES $WARNINGS -ldl
else
    if [ "$GTEST"=="true" ]; then
        clang++-3.8 $WARNING_LEVEL "preprocessor/preprocessor.cpp" "preprocessor/google_test/gtest-all.cc" $CPP_VERSION $DISABLED -o $OUTPUT_NAME -DERROR_LOGGING=1 -DRUN_TESTS=1 -DINTERNAL=1 -DMEM_CHECK=1 $DEFINES $WARNINGS -g -ldl -pthread
    else
        clang++-3.8 $WARNING_LEVEL "preprocessor/preprocessor.cpp" $CPP_VERSION $DISABLED -o $OUTPUT_NAME -DERROR_LOGGING=1 -DRUN_TESTS=0 -DINTERNAL=1 -DMEM_CHECK=1 $DEFINES $WARNINGS -g -ldl
    fi
fi
mv "./preprocessor_exe" "builds/preprocessor"

# GCC
if [ "$RUN_GCC_FOR_EXTRA_TEST"=="true" ]; then
    COMMON_WARNINGS_GCC="-Wno-unused-variable -Wno-write-strings -Wno-switch -Wno-sign-compare -Wno-missing-field-initializers -Wno-unused-parameter"
    gcc -Wall -Wextra "preprocessor/preprocessor.cpp" -std=c++11 -o preprocessor_gcc -DERROR_LOGGING=1 -DRUN_TESTS=0 -DINTERNAL=1 -DMEM_CHECK=1 -DWIN32=0 -DLINUX=1 $COMMON_WARNINGS_GCC -g -ldl -pthread
    rm "./preprocessor_gcc"
fi

# Run code after building.
if [ "$GTEST"=="true" ]; then
    if [ "$RELEASE"=="false" ]; then      
        ./builds/preprocessor -t
    fi
fi

# Test.
if [ "$RUN_TEST_CODE"=="true" ]; then
    pushd "test"
    "../builds/preprocessor" test_code.cpp
    popd

    clang++-3.8 -Wall -Wextra "test/test_code.cpp" -std=c++11 -o test_exe -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-c++11-compat-deprecated-writable-strings -g -ldl
    mv "./test_exe" "builds/test"
fi

