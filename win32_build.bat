@echo off

rem Variables to set.
rem Can be x86 or x64.
SET ENVIRONMENT=x86

rem Whether to run tests or not.
SET TESTS=false

rem A release build.
SET RELEASE=false

rem Warnings to ignore.
set COMMON_WARNINGS=-wd4189 -wd4706 -wd4996 -wd4100 -wd4127 -wd4267 -wd4505 -wd4820 -wd4365 -wd4514 -wd4062 -wd4061 -wd4668 -wd4389 -wd4018 -wd4711



rem Actual build.
pushd "p:/preprocessor"

rem 32/64 bit builds.
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" %ENVIRONMENT%

rem Preprocessor.

setlocal EnableDelayedExpansion
set COMMON_COMPILER_FLAGS=-MTd -nologo -Gm- -GR- -EHa- -Od -Oi %COMMON_WARNINGS% -DINTERNAL=1 -DWIN32=1 -DLINUX=0 -FC -Zi -GS- -Gs9999999
if "%RELEASE%"=="true" (
    set COMMON_COMPILER_FLAGS=-MTd -nologo -fp:fast -Gm- -GR- -EHa- -O2 -Oi %COMMON_WARNINGS% -DINTERNAL=0 -DWIN32=1 -DLINUX=0 -FC -Zi -GS- -Gs9999999
)

IF NOT EXIST "../builds/preprocessor_build" mkdir "../builds/preprocessor_build"
pushd "../builds/preprocessor_build"

REM Main code. 
cl -FePreprocessor %COMMON_COMPILER_FLAGS% -Wall "p:/preprocessor/preprocessor/platform_win32.cpp" "p:/preprocessor/preprocessor/preprocessor.cpp" -link -subsystem:console,5.2 -NODEFAULTLIB kernel32.lib
popd rem "../builds/preprocessor_build"

rem Tests.
if "%TESTS%"=="true" (
    rem Test code C++
    IF NOT EXIST "../builds/preprocessor_test_cpp_build" mkdir "../builds/preprocessor_test_cpp_build"
    pushd "../builds/preprocessor_test_cpp_build"
    
    rem Call preprocessor.
    pushd "../../preprocessor/test_cpp"
    "../../builds/preprocessor_build/preprocessor.exe" test_main.cpp test_file.cpp
    popd rem "../../preprocessor/test_cpp"
    
    REM Build test code.
    cl %COMMON_COMPILER_FLAGS% -Wall "p:/preprocessor/test_cpp/test_main.cpp" "p:/preprocessor/test_cpp/test_file.cpp" "p:/preprocessor/test_cpp/generated.cpp" -FmTest.map -link -subsystem:console,5.2 kernel32.lib
    
    popd rem "../builds/preprocessor_test_cpp_build"
    
    
    rem Test code C
    IF NOT EXIST "../builds/preprocessor_test_c_build" mkdir "../builds/preprocessor_test_c_build"
    pushd "../builds/preprocessor_test_c_build"
    
    rem Call preprocessor.
    pushd "../../preprocessor/test_c"
    "../../builds/preprocessor_build/preprocessor.exe" test_main.c
    popd rem "../../preprocessor/test_c"
    
    REM Build test code.
    cl -TC %COMMON_COMPILER_FLAGS% -Wall "../../preprocessor/test_c/test_main.c" "../../preprocessor/test_c/generated.c" -FmTest.map -link -subsystem:console,5.2 kernel32.lib
    
    popd rem "../builds/preprocessor_test_c_build"
)

popd rem "p:/preprocessor"