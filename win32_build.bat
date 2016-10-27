@echo off

rem Variables to set.
rem Can be x86 or x64.
set ENVIRONMENT=x86

rem Whether to run tests or not.
set TESTS=true

rem A release build.
set RELEASE=false

rem Warnings to ignore.
set COMMON_WARNINGS=-wd4189 -wd4706 -wd4996 -wd4100 -wd4127 -wd4267 -wd4505 -wd4820 -wd4365 -wd4514 -wd4062 -wd4061 -wd4668 -wd4389 -wd4018 -wd4711

rem Build stuff.

rem 32/64 bit builds.
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" %ENVIRONMENT%

rem Preprocessor.

setlocal EnableDelayedExpansion
set COMMON_COMPILER_FLAGS=-nologo -Gm- -GR- -EHa- -Od -Oi %COMMON_WARNINGS% -DINTERNAL=1 -DWIN32=1 -DLINUX=0 -FC -Zi -GS- -Gs9999999
if "%RELEASE%"=="true" (
    set COMMON_COMPILER_FLAGS=-nologo -fp:fast -Gm- -GR- -EHa- -O2 -Oi %COMMON_WARNINGS% -DINTERNAL=0 -DWIN32=1 -DLINUX=0 -FC -Zi -GS- -Gs9999999
)

IF NOT EXIST "builds/win32_msvc" mkdir "builds/win32_msvc"
pushd "builds/win32_msvc"
cl -FePreprocessor %COMMON_COMPILER_FLAGS% -Wall "../../preprocessor/platform_win32.cpp" "../../preprocessor/preprocessor.cpp" -link -subsystem:console,5.2 -NODEFAULTLIB kernel32.lib
popd

rem Tests.
if "%TESTS%"=="true" (
    rem Test code C++
    IF NOT EXIST "builds/win32_msvc" mkdir "builds/win32_msvc"
    pushd "builds/win32_msvc"
    

    rem Call preprocessor.
    pushd "../../test_cpp"
    "../builds/win32_msvc/preprocessor.exe" test_main.cpp test_file.cpp
    popd
    
    REM Build test code.
    cl -FeTestCPP -MTd %COMMON_COMPILER_FLAGS% -Wall "../../test_cpp/test_main.cpp" "../../test_cpp/test_file.cpp" "../../test_cpp/generated.cpp" -FmTest.map -link -subsystem:console,5.2 kernel32.lib
    
    
    rem Test code C
    
    rem Call preprocessor.
    pushd "../../test_c"
    "../builds/win32_msvc/preprocessor.exe" test_main.c
    popd
    
    REM Build test code.
    cl -TC -FeTestC -MTd %COMMON_COMPILER_FLAGS% -Wall "../../test_c/test_main.c" "../../test_c/generated.c" -FmTest.map -link -subsystem:console,5.2 kernel32.lib
    

    rem Test SDL.
    
    rem Call preprocessor.
    pushd "../../app test"
    "../builds/win32_msvc/preprocessor.exe" sdl_main.cpp
    popd
    
    REM Build test code.
    cl -FeTestSDL -MDd %COMMON_COMPILER_FLAGS% -Wall "../../app test/sdl_main.cpp" -FmTest.map -link -subsystem:windows,5.2 kernel32.lib SDL2.lib SDL2main.lib
)
