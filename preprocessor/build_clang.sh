# Batch File to compile Frozen on Linux

mkdir -p "/home/jonathan/Desktop/builds/preprocessor_build"
cd "/home/jonathan/Desktop/builds/preprocessor_build"

# Build preprocessor
# Platform Code.
clang++ "/home/jonathan/Desktop/projects/preprocessor/platform_linux.cpp" "/home/jonathan/Desktop/projects/preprocessor/preprocessor.cpp" -std=c++1y -o preprocessor_platform -DENVIRONMENT64 -DINTERNAL -Wno-deprecated-declarations -Wno-unused-parameter -Wno-missing-prototypes -Wno-unused-function -Wno-unused-variable -Wno-padded -Wno-float-equal -Wno-conversion -Wno-missing-field-initializers -Wno-missing-braces -Wno-missing-variable-declarations -Wno-format-nonliteral -Wno-cast-align -Wno-switch-enum -Wno-incompatible-pointer-types-discards-qualifiers -Wno-unused-macros -Wno-typedef-redefinition -Wno-format -Wno-c++11-compat-deprecated-writable-strings -Wno-switch -g -ldl

# Call preprocessor
pushd "/home/jonathan/Desktop/projects/preprocessor"
"/home/jonathan/Desktop/builds/preprocessor_build/preprocessor_platform" test_main.cpp test_file.cpp
popd

# Build test
clang++ "/home/jonathan/Desktop/projects/preprocessor/test_main.cpp" "/home/jonathan/Desktop/projects/preprocessor/test_file.cpp" "/home/jonathan/Desktop/projects/preprocessor/generated.cpp" -std=c++1y -o preprocessor_test -Wno-deprecated-declarations -Wno-unused-parameter -Wno-missing-prototypes -Wno-unused-function -Wno-unused-variable -Wno-padded -Wno-float-equal -Wno-conversion -Wno-missing-field-initializers -Wno-missing-braces -Wno-missing-variable-declarations -Wno-format-nonliteral -Wno-cast-align -Wno-switch-enum -Wno-incompatible-pointer-types-discards-qualifiers -Wno-unused-macros -Wno-typedef-redefinition -Wno-format -Wno-c++11-compat-deprecated-writable-strings -Wno-switch -g
