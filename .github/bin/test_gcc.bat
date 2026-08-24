set INSTALL_DIR=%CD%\ci_install
set PATH=%INSTALL_DIR%\bin;%PATH%
set CLOWNFISH_INCLUDE=%INSTALL_DIR%\share\clownfish\include

"C:\Program Files\Git\bin\git" clone --depth=1 https://github.com/lucysearch/lucy-clownfish.git || exit /b 1

cd lucy-clownfish\compiler\c
call configure.bat --prefix=%INSTALL_DIR% || exit /b 1
mingw32-make || exit /b 1
mingw32-make install || exit /b 1

cd ..\..\runtime\c
call configure.bat --prefix=%INSTALL_DIR% || exit /b 1
mingw32-make || exit /b 1
mingw32-make install || exit /b 1

cd ..\..\..\c
call configure.bat --clownfish-prefix=%INSTALL_DIR% || exit /b 1
mingw32-make || exit /b 1
mingw32-make test || exit /b 1
