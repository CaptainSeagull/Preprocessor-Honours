@echo off

rem Variables to set. NOTE - Google Test uses _a lot_ of memory, so it's advised to run tests in 64-bit.
set VISUAL_STUDIO_VERSION=10
set ENVIRONMENT=x86
set RELEASE=false
set RUN_CODE_AFTER_BUILDING=true

set RUN_TEST=false
set RUN_BREAKOUT=true

rem Warnings to ignore.
set COMMON_WARNINGS=-wd4189 -wd4706 -wd4996 -wd4100 -wd4127 -wd4267 -wd4505 -wd4820 -wd4365 -wd4514 -wd4062 -wd4061 -wd4668 -wd4389 -wd4018 -wd4711 -wd4987 -wd4710 -wd4625 -wd4626 -wd4350 -wd4826 -wd4640 -wd4571 -wd4986 -wd4388 -wd4129
 
rem 32/64 bit builds.
call "C:\Program Files (x86)\Microsoft Visual Studio %VISUAL_STUDIO_VERSION%.0\VC\vcvarsall.bat" %ENVIRONMENT%

set COMMON_COMPILER_FLAGS=-nologo -MTd -Gm- -GR- -EHsc- -Od -Oi %COMMON_WARNINGS% -DERROR_LOGGING=1 -DRUN_TESTS=0 -DINTERNAL=1 -DMEM_CHECK=0 -DWIN32=1 -DLINUX=0 -FC -Zi -GS- -Gs9999999

setlocal EnableDelayedExpansion
set FILES="../preprocessor/preprocessor.cpp" "../preprocessor/google_test/gtest-all.cc"
if "%RELEASE%"=="true" (
    set COMMON_COMPILER_FLAGS=-nologo -MT -fp:fast -Gm- -GR- -EHa- -O2 -Oi %COMMON_WARNINGS% -DINTERNAL=0 -DWIN32=1 -DLINUX=0 -FC -Zi -GS- -Gs9999999
    set FILES="../preprocessor/preprocessor.cpp"
)

IF NOT EXIST "build" mkdir "build"
pushd "build"

cl -FePreprocessor %COMMON_COMPILER_FLAGS% -Wall %FILES% -link -subsystem:console,5.2 kernel32.lib
popd

if "%RUN_CODE_AFTER_BUILDING%"=="true" (
    "build/preprocessor.exe" -t
)

if "%RUN_TEST%"=="true" (
    pushd "test"
    "../build/preprocessor.exe" test_code.cpp -p
    popd

    pushd "build"
    cl -FeTestCode %COMMON_COMPILER_FLAGS% -Wall "../test/test_code.cpp" -FmTest.map -link -subsystem:console,5.2 kernel32.lib
    popd
)

if "%RUN_BREAKOUT%"=="true" (
    rem pushd "breakout"
    rem "../build/preprocessor.exe" test_code.cpp -p
    rem popd

    pushd "build"
    cl -FeBreakout %COMMON_COMPILER_FLAGS% -wd4201 -Wall "../breakout/win32.cpp" -FmTest.map -link -subsystem:windows,5.2 kernel32.lib user32.lib gdi32.lib opengl32.lib winmm.lib dsound.lib
    popd
)
