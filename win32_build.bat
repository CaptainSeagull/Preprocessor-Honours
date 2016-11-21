@echo off

rem Variables to set.

rem Version of Visual Studio to use.
set VISUAL_STUDIO_VERSION=10.0

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
call "C:\Program Files (x86)\Microsoft Visual Studio %VISUAL_STUDIO_VERSION%\VC\vcvarsall.bat" %ENVIRONMENT%

rem Preprocessor.

setlocal EnableDelayedExpansion
set COMMON_COMPILER_FLAGS=-nologo -MDd -Gm- -GR- -EHa- -Od -Oi %COMMON_WARNINGS% -DINTERNAL=1 -DWIN32=1 -DLINUX=0 -FC -Zi -GS- -Gs9999999
if "%RELEASE%"=="true" (
    set COMMON_COMPILER_FLAGS=-nologo -MD -fp:fast -Gm- -GR- -EHa- -O2 -Oi %COMMON_WARNINGS% -DINTERNAL=0 -DWIN32=1 -DLINUX=0 -FC -Zi -GS- -Gs9999999
)

IF NOT EXIST "builds/win32_msvc" mkdir "builds/win32_msvc"
pushd "builds/win32_msvc"
cl -FePreprocessor %COMMON_COMPILER_FLAGS% -Wall "../../preprocessor/preprocessor.cpp" -link -subsystem:console,5.2 kernel32.lib
popd

rem Tests.
if "%TESTS%"=="true" (
    rem Test code C++
    IF NOT EXIST "builds/win32_msvc" mkdir "builds/win32_msvc"
    
    rem Call preprocessor.
    pushd "tests"
    
    "../builds/win32_msvc/preprocessor.exe" -s test0.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test1.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test2.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test3.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test4.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test5.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test6.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test7.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test8.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test9.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test10.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test11.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test12.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test13.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test14.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test15.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test16.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test17.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test18.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test19.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test20.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test21.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test22.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test23.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test24.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test25.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test26.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test27.cpp
    "../builds/win32_msvc/preprocessor.exe" -s test28.cpp
    
    popd
)

rem Test SDL.

rem Call preprocessor.
pushd "app test"
"../builds/win32_msvc/preprocessor.exe" sdl_main.cpp
popd
    
REM Build test code.
rem cl -FeTestSDL %COMMON_COMPILER_FLAGS% -wd4098 -Wall "../../app test/sdl_main.cpp" "../../app test/generated.cpp" -FmTest.map -link -subsystem:windows,5.2 kernel32.lib SDL2.lib SDL2main.lib
