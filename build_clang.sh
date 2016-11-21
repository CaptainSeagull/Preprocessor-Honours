# Batch File to compile Frozen on Linux

mkdir -p "builds/linux_clang"
pushd "builds/linux_clang"


# Build preprocessor
clang++ -Wall "../../preprocessor/preprocessor.cpp" -std=c++1y -o preprocessor -DINTERNAL=1 -DERROR_LOGGING=1 -Wno-unused-function -Wno-c++11-compat-deprecated-writable-strings -Wno-switch -g -ldl


# Tests.
pushd "../../tests"

"../builds/linux_clang/preprocessor" -s test0.cpp
"../builds/linux_clang/preprocessor" -s test1.cpp
"../builds/linux_clang/preprocessor" -s test2.cpp
"../builds/linux_clang/preprocessor" -s test3.cpp
"../builds/linux_clang/preprocessor" -s test4.cpp
"../builds/linux_clang/preprocessor" -s test5.cpp
"../builds/linux_clang/preprocessor" -s test6.cpp
"../builds/linux_clang/preprocessor" -s test7.cpp
"../builds/linux_clang/preprocessor" -s test8.cpp
"../builds/linux_clang/preprocessor" -s test9.cpp
"../builds/linux_clang/preprocessor" -s test10.cpp
"../builds/linux_clang/preprocessor" -s test11.cpp
"../builds/linux_clang/preprocessor" -s test12.cpp
"../builds/linux_clang/preprocessor" -s test13.cpp
"../builds/linux_clang/preprocessor" -s test14.cpp
"../builds/linux_clang/preprocessor" -s test15.cpp
"../builds/linux_clang/preprocessor" -s test16.cpp
"../builds/linux_clang/preprocessor" -s test17.cpp
"../builds/linux_clang/preprocessor" -s test18.cpp
"../builds/linux_clang/preprocessor" -s test19.cpp
"../builds/linux_clang/preprocessor" -s test20.cpp
"../builds/linux_clang/preprocessor" -s test21.cpp
"../builds/linux_clang/preprocessor" -s test22.cpp
"../builds/linux_clang/preprocessor" -s test23.cpp
"../builds/linux_clang/preprocessor" -s test24.cpp
"../builds/linux_clang/preprocessor" -s test25.cpp
"../builds/linux_clang/preprocessor" -s test26.cpp
"../builds/linux_clang/preprocessor" -s test27.cpp
"../builds/linux_clang/preprocessor" -s test28.cpp

popd

# Build SDL test.
# g++ -o sdl_test sdl_main.cpp lSDL
pushd "../../app test"
"../builds/linux_clang/preprocessor" sdl_main.cpp

clang -Wall "sdl_main.cpp" -std=c++1y -o sdl_test generated.cpp -Wno-switch -g -lSDL2
mv "./sdl_test" "../builds/linux_clang/app_test"
popd


popd