@echo off

rem Variables to set.
set VISUAL_STUDIO_VERSION=12
set ENVIRONMENT=x86
set RELEASE=false
set RUN_CODE_AFTER_BUILDING=true
set GTEST=false

set RUN_TEST=true
set RUN_BREAKOUT=false

rem Warnings to ignore.
set COMMON_WARNINGS=-wd4189 -wd4706 -wd4996 -wd4100 -wd4127 -wd4267 -wd4505 -wd4820 -wd4365 -wd4514 -wd4062 -wd4061 -wd4668 -wd4389 -wd4018 -wd4711 -wd4987 -wd4710 -wd4625 -wd4626 -wd4350 -wd4826 -wd4640 -wd4571 -wd4986 -wd4388 -wd4129 -wd4201
 
rem 32/64 bit builds.
call "C:\Program Files (x86)\Microsoft Visual Studio %VISUAL_STUDIO_VERSION%.0\VC\vcvarsall.bat" %ENVIRONMENT%

IF NOT EXIST "build" mkdir "build"

set DEBUG_COMMON_COMPILER_FLAGS=-nologo -MTd -Gm- -GR- -EHsc- -Od -Oi %COMMON_WARNINGS% -DERROR_LOGGING=1 -DRUN_TESTS=0 -DINTERNAL=1 -DMEM_CHECK=1 -DWIN32=1 -DLINUX=0 -FC -Zi -GS- -Gs9999999
set RELEASE_COMMON_COMPILER_FLAGS=-nologo -MT -fp:fast -Gm- -GR- -EHa- -O2 -Oi %COMMON_WARNINGS% -DERROR_LOGGING=0 -DRUN_TESTS=0 -DINTERNAL=0 -DMEM_CHECK=0 -DWIN32=1 -DLINUX=0 -FC -Zi -GS- -Gs9999999

rem Build prepreprocessor.
set FILES="../preprocessor/main.cpp" "../preprocessor/utils.cpp" "../preprocessor/lexer.cpp" "../preprocessor/platform_win32.cpp" "../preprocessor/write_file.cpp"
pushd "build"
if "%RELEASE%"=="true" (
    cl -FePreprocessor %RELEASE_COMMON_COMPILER_FLAGS% -Wall %FILES% -link -subsystem:console,5.2 kernel32.lib
) else (
    if "%GTEST%"=="true" (
        cl -FePreprocessor %DEBUG_COMMON_COMPILER_FLAGS% -DRUN_TESTS=1 -Wall %FILES% "../preprocessor/google_test/gtest-all.cc" -link -subsystem:console,5.2 kernel32.lib
    ) else (
        cl -FePreprocessor %DEBUG_COMMON_COMPILER_FLAGS% -DRUN_TESTS=0 -Wall %FILES% -link -subsystem:console,5.2 kernel32.lib
    )
)
popd

rem Run after building.
if "%RUN_CODE_AFTER_BUILDING%"=="true" (
    "build/preprocessor.exe" -t
)

rem Test code.
if "%RUN_TEST%"=="true" (
    pushd "test"
    "../build/preprocessor.exe" test_code.cpp -p
    popd

    pushd "build"
    cl -FeTestCode %DEBUG_COMMON_COMPILER_FLAGS% -Wall "../test/test_code.cpp" -FmTest.map -link -subsystem:console,5.2 kernel32.lib
    popd
)

rem Breakout.
set SDL_COMMON_COMPILER_FLAGS=-nologo -MDd -Gm- -GR- -EHsc- -Od -Oi %COMMON_WARNINGS% -DERROR_LOGGING=1 -DRUN_TESTS=0 -DINTERNAL=1 -DMEM_CHECK=0 -DWIN32=1 -DLINUX=0 -FC -Zi -GS- -Gs9999999
if "%RUN_BREAKOUT%"=="true" (
    pushd "breakout"
    "../build/preprocessor.exe" breakout.cpp -e
    popd

    pushd "build"
    cl -FeBreakout %SDL_COMMON_COMPILER_FLAGS% -MDd -Wall "../breakout/breakout.cpp" -FmTest.map -link -subsystem:windows,5.2 -NODEFAULTLIB:msvcrt.lib kernel32.lib user32.lib gdi32.lib opengl32.lib winmm.lib dsound.lib sdl2.lib sdl2main.lib
    popd
)
