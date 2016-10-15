pushd "p:/preprocessor"

rem Uncomment one or the other for 32/64 bit builds.
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86
rem call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x64

rem Preprocessor
call "preprocessor/win32_build_preprocessor.bat"

rem Test code
call "test/win32_build_test.bat"

popd