# Batch File to compile the preprocessor on Linux.

RELEASE=false
GTEST=true
RUN_TEST_CODE=true
RUN_GCC_FOR_EXTRA_TEST=false

# Preprocessor
pushd "preprocessor"

COMMON_WARNINGS_CLANG="-Wno-unused-function -Wno-unused-variable -Wno-c++11-compat-deprecated-writable-strings -Wno-switch -Wno-sign-compare -Wno-unused-parameter"

if [ "$RELEASE" == "true" ]; then
    clang++ -Wall -Wextra "preprocessor.cpp" -std=c++11 -o preprocessor -DERROR_LOGGING=0 -DRUN_TESTS=0 -DINTERNAL=0 -DMEM_CHECK=0 -DWIN32=0 -DLINUX=1 $COMMON_WARNINGS_CLANG -ldl
else
    if [ "$GTEST" == "true" ]; then
        clang++ -Wall -Wextra "preprocessor.cpp" "google_test/gtest-all.cc" -std=c++11 -o preprocessor -DERROR_LOGGING=1 -DRUN_TESTS=1 -DINTERNAL=1 -DMEM_CHECK=1 -DWIN32=0 -DLINUX=1 $COMMON_WARNINGS_CLANG -g -ldl -pthread
    else
        clang++ -Wall -Wextra "preprocessor.cpp" -std=c++11 -o preprocessor -DERROR_LOGGING=1 -DRUN_TESTS=0 -DINTERNAL=1 -DMEM_CHECK=1 -DWIN32=0 -DLINUX=1 $COMMON_WARNINGS_CLANG -g -ldl -pthread
    fi
fi
mv "./preprocessor" "../builds/linux_clang/preprocessor"

# GCC
if [ "$RUN_GCC_FOR_EXTRA_TEST" == "true" ]; then
    COMMON_WARNINGS_GCC="-Wno-write-strings -Wno-switch -Wno-sign-compare -Wno-missing-field-initializers -Wno-unused-parameter"
    gcc -Wall -Wextra "preprocessor.cpp" -std=c++11 -o preprocessor_gcc -DERROR_LOGGING=1 -DRUN_TESTS=0 -DINTERNAL=1 -DMEM_CHECK=1 -DWIN32=0 -DLINUX=1 $COMMON_WARNINGS_GCC -g -ldl -pthread
    rm "./preprocessor_gcc"
fi

popd

# Run code after building.
if [ "$GTEST" == "true" ]; then
    if [ "$RELEASE" == "false" ]; then      
        ./builds/linux_clang/preprocessor -t
    fi
fi

# Test.
if [ "$RUN_TEST_CODE" == "true" ]; then
    pushd "test"
    "../builds/linux_clang/preprocessor" test_code.cpp

    clang++ -Wall "test_code.cpp" -std=c++11 -o text_exe -Wno-unused-function -Wno-unused-variable -g -ldl
    mv "./text_exe" "../builds/linux_clang/text"
fi

