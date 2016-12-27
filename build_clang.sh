# Batch File to compile the preprocessor on Linux.

RELEASE=true
RUN_CODE_AFTER_BUILDING=true
RUN_TEST=true
RUN_GCC_FOR_EXTRA_TEST=true

# Preprocessor
pushd "preprocessor"

COMMON_WARNINGS="-Wno-unused-function -Wno-c++11-compat-deprecated-writable-strings -Wno-switch -Wno-sign-compare -Wno-unused-parameter"

if [ "$RELEASE" == "$true" ]; then
    clang++ -Wall "preprocessor.cpp" -std=c++11 -o preprocessor -DERROR_LOGGING=0 -DRUN_TESTS=0 -DINTERNAL=0 -DMEM_CHECK=0 -DWIN32=0 -DLINUX=1 $COMMON_WARNINGS -ldl 
else
    clang++ -Wall -Wextra "preprocessor.cpp" -std=c++11 -o preprocessor -DERROR_LOGGING=1 -DRUN_TESTS=0 -DINTERNAL=1 -DMEM_CHECK=1 -DWIN32=0 -DLINUX=1 $COMMON_WARNINGS -g -ldl -pthread
fi
mv "./preprocessor" "../builds/linux_clang/preprocessor"

# GCC
if [ "$RELEASE" == "$true" ]; then
    COMMON_WARNINGS="-Wno-write-strings -Wno-switch -Wno-sign-compare -Wno-missing-field-initializers -Wno-unused-parameter"
    gcc -Wall -Wextra "preprocessor.cpp" -std=c++11 -o preprocessor_gcc -DERROR_LOGGING=1 -DRUN_TESTS=0 -DINTERNAL=1 -DMEM_CHECK=1 -DWIN32=0 -DLINUX=1 $COMMON_WARNINGS -g -ldl -pthread
    rm "./preprocessor_gcc"
fi

popd

# Run code after building.
if [ "$RUN_CODE_AFTER_BUILDING%"=="true" ]; then
    ./builds/linux_clang/preprocessor -t
fi

# Test.
pushd "test"
"../builds/linux_clang/preprocessor" test_code.cpp

clang++ -Wall "test_code.cpp" -std=c++11 -o text_exe -Wno-unused-function -Wno-unused-variable -g -ldl
mv "./text_exe" "../builds/linux_clang/text"

