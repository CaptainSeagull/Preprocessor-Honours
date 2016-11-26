# Batch File to compile Frozen on Linux

# Build preprocessor
pushd preprocessor
clang++ -Wall "preprocessor.cpp" "google_test/gtest-all.cc" -std=c++1y -o preprocessor -DINTERNAL=1 -DERROR_LOGGING=1 -Wno-unused-function -Wno-c++11-compat-deprecated-writable-strings -Wno-switch -g -ldl -pthread
mv "./preprocessor" "../builds/linux_clang/preprocessor"
popd