@echo off

set COMMON_WARNINGS= -wd4189 -wd4706 -wd4996 -wd4100 -wd4127 -wd4267 -wd4505 -wd4820 -wd4365 -wd4514 -wd4062 -wd4061 -wd4668
set COMMON_COMPILER_FLAGS=-MTd -nologo -fp:fast -Gm- -GR- -EHa- -Od -Oi %COMMON_WARNINGS% -DINTERNAL=1 -DENVIRONMENT32=1 -DWIN32=1 -DLINUX=0 -FC -Zi -GS- -Gs9999999

IF NOT EXIST "../../builds/preprocessor_build" mkdir "../../builds/preprocessor_build"
pushd "../../builds/preprocessor_build"

REM Main code. 
cl %COMMON_COMPILER_FLAGS% -Wall "p:/preprocessor/preprocessor/platform_win32.cpp" "p:/preprocessor/preprocessor/preprocessor.cpp" -link -subsystem:console,5.2 -NODEFAULTLIB kernel32.lib

popd