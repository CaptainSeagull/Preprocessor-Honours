@echo off

rem Variables to set.
set VISUAL_STUDIO_VERSION=12
set ENVIRONMENT=x86
set RELEASE=false
set RUN_SDL_CODE=false


rem Warnings to ignore.
set COMMON_WARNINGS=-wd4189 -wd4706 -wd4996 -wd4100 -wd4127 -wd4267 -wd4505 -wd4820 -wd4365 -wd4514 -wd4062 -wd4061 -wd4668 -wd4389 -wd4018 -wd4711

rem 32/64 bit builds.
call "C:\Program Files (x86)\Microsoft Visual Studio %VISUAL_STUDIO_VERSION%.0\VC\vcvarsall.bat" %ENVIRONMENT%

set COMMON_COMPILER_FLAGS=-nologo -MDd -Gm- -GR- -EHsc- -Od -Oi %COMMON_WARNINGS% -DINTERNAL=1 -DWIN32=1 -DLINUX=0 -FC -Zi -GS- -Gs9999999

setlocal EnableDelayedExpansion
set FILES="../../preprocessor/preprocessor.cpp" "../../preprocessor/gtest-all.cc"
if "%RELEASE%"=="true" (
    set COMMON_COMPILER_FLAGS=-nologo -MD -fp:fast -Gm- -GR- -EHa- -O2 -Oi %COMMON_WARNINGS% -DINTERNAL=0 -DWIN32=1 -DLINUX=0 -FC -Zi -GS- -Gs9999999
    set FILES="../../preprocessor/preprocessor.cpp"
)

IF NOT EXIST "builds/win32_msvc" mkdir "builds/win32_msvc"
pushd "builds/win32_msvc"
cl -FePreprocessor %COMMON_COMPILER_FLAGS% -W4 %FILES% -link -subsystem:console,5.2 kernel32.lib
popd


if "%ENVIRONMENT%"=="x86" (
    if "%RUN_SDL_CODE%"=="true" (
        pushd "app test"
        "../builds/win32_msvc/preprocessor.exe" sdl_main.cpp
        popd
        
        pushd "builds/win32_msvc"
        cl -FeTestSDL %COMMON_COMPILER_FLAGS% -wd4098 -Wall "../../app test/sdl_main.cpp" -FmTest.map -link -subsystem:windows,5.2 kernel32.lib SDL2.lib SDL2main.lib
        popd
    )
)