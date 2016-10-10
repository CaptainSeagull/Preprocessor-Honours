@echo off

set COMMON_WARNINGS= -wd4189 -wd4706 -wd4996 -wd4100 -wd4127 -wd4267 -wd4505 -wd4820 -wd4365 -wd4514 -wd4062 -wd4061 -wd4668
set COMMON_COMPILER_FLAGS=-MTd -nologo -fp:fast -Gm- -GR- -EHa- -Od -Oi %COMMON_WARNINGS% -DINTERNAL=1 -DENVIRONMENT64=1 -DWIN32=1 -DLINUX=0 -FC -Zi -GS- -Gs9999999

IF NOT EXIST "../../builds/preprocessor_test_build" mkdir "../../builds/preprocessor_test_build"
pushd "../../builds/preprocessor_test_build"

rem Call preprocessor.
pushd "../../preprocessor/test"
"../../builds/preprocessor_build/platform_win32.exe" test_main.cpp test_file.cpp
popd

REM Build test code.
cl %COMMON_COMPILER_FLAGS% -Wall "../../preprocessor/test/test_main.cpp" "../../preprocessor/test/test_file.cpp" "../../preprocessor/test/generated.cpp" -FmTest.map -link -subsystem:console,5.2 kernel32.lib

popd