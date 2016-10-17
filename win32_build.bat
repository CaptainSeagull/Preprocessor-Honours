@echo off
rem Build

rem 32/64 bit builds.
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86
rem call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x64

rem Preprocessor
set COMMON_WARNINGS= -wd4189 -wd4706 -wd4996 -wd4100 -wd4127 -wd4267 -wd4505 -wd4820 -wd4365 -wd4514 -wd4062 -wd4061 -wd4668 -wd4389 -wd4018
set COMMON_COMPILER_FLAGS=-MTd -nologo -fp:fast -Gm- -GR- -EHa- -Od -Oi %COMMON_WARNINGS% -DINTERNAL=1 -DENVIRONMENT32=1 -DWIN32=1 -DLINUX=0 -FC -Zi -GS- -Gs9999999

IF NOT EXIST "../builds/preprocessor_build" mkdir "../builds/preprocessor_build"
pushd "../builds/preprocessor_build"

REM Main code. 
cl -FePreprocessor %COMMON_COMPILER_FLAGS% -Wall "p:/preprocessor/preprocessor/platform_win32.cpp" "p:/preprocessor/preprocessor/preprocessor.cpp" -link -subsystem:console,5.2 -NODEFAULTLIB kernel32.lib
popd


rem Test code
IF NOT EXIST "../builds/preprocessor_test_build" mkdir "../builds/preprocessor_test_build"
pushd "../builds/preprocessor_test_build"

rem Call preprocessor.
pushd "../../preprocessor/test"
"../../builds/preprocessor_build/preprocessor.exe" test_main.cpp test_file.cpp
popd

REM Build test code.
cl %COMMON_COMPILER_FLAGS% -Wall "../../preprocessor/test/test_main.cpp" "../../preprocessor/test/test_file.cpp" "../../preprocessor/test/generated.cpp" -FmTest.map -link -subsystem:console,5.2 kernel32.lib

popd