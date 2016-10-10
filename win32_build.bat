pushd "p:/preprocessor"

rem Preprocessor
call "preprocessor/win32_build_preprocessor.bat"

rem Test code
call "test/win32_build_test.bat"

popd