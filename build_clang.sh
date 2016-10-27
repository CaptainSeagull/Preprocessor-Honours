# Batch File to compile Frozen on Linux

mkdir -p "builds/linux_clang"
pushd "builds/linux_clang"


# Build preprocessor
clang++ -Wall "../../preprocessor/platform_linux.cpp" "../../preprocessor/preprocessor.cpp" -std=c++1y -o preprocessor -DINTERNAL -Wno-unused-function -Wno-c++11-compat-deprecated-writable-strings -Wno-switch -g -ldl


# Build CPP test.
pushd "../../test_cpp"
"../builds/linux_clang/preprocessor" test_main.cpp test_file.cpp

clang++ -Wall "test_main.cpp" "test_file.cpp" "generated.cpp" -std=c++1y -o preprocessor_test_cpp -Wno-unused-variable -Wno-unused-function -Wno-switch -g
mv "./preprocessor_test_cpp" "../builds/linux_clang/preprocessor_test_cpp"
popd


# Build C test.
pushd "../../test_c"
"../builds/linux_clang/preprocessor" test_main.c

clang -Wall "test_main.c" "generated.c" -std=c89 -o preprocessor_test_c -Wno-comment -Wno-switch -g
mv "./preprocessor_test_c" "../builds/linux_clang/preprocessor_test_c"
popd


# Build SDL test.
# g++ -o sdl_test sdl_main.cpp lSDL
pushd "../../app test"
"../builds/linux_clang/preprocessor" sdl_main.cpp

clang -Wall "sdl_main.cpp" -std=c++1y -o sdl_test -Wno-switch -g -lSDL2
mv "./sdl_test" "../builds/linux_clang/app_test"
popd


popd