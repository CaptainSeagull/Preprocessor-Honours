# Batch File to compile the preprocessor on Linux.

# Preprocessor
pushd preprocessor

clang++ -Wall "preprocessor.cpp" "google_test/gtest-all.cc" -std=c++1y -o preprocessor -DINTERNAL=1 -DERROR_LOGGING=1 -Wno-unused-function -Wno-c++11-compat-deprecated-writable-strings -Wno-switch -g -ldl -pthread
mv "./preprocessor" "../builds/linux_clang/preprocessor"

popd

# SDL
#pushd "app test"
#"../builds/linux_clang/preprocessor" sdl_main.cpp sdl_other.cpp
#
#clang++ -Wall "sdl_main.cpp" "sdl_other.cpp" -std=c++1y -o app_test -DINTERNAL=1 -DERROR_LOGGING=1 -Wno-unused-function -Wno-c++11-compat-deprecated-writable-strings -Wno-switch -Wno-unused-variable -g -ldl -pthread -lSDL2
#mv "./app_test" "../builds/linux_clang/app_test"
#
#popd

# SDL
pushd "test"
"../builds/linux_clang/preprocessor" test_code.cpp

clang++ -Wall "test_code.cpp" -std=c++1y -o text_exe -Wno-unused-function -Wno-c++11-compat-deprecated-writable-strings -Wno-switch -Wno-unused-variable -g -ldl
mv "./text_exe" "../builds/linux_clang/text_exe"


popd

