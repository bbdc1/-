@echo off
chcp 65001 >nul
echo ====================================
echo Building Snake Game with MinGW
echo ====================================
echo.

REM 设置 MinGW 编译器路径
set MINGW_PATH=D:\PATH\minggw\mingw64\bin

REM 检查编译器是否存在
if not exist "%MINGW_PATH%\g++.exe" (
    echo Error: g++ not found at %MINGW_PATH%
    echo Please check your MinGW installation path
    pause
    exit /b 1
)

echo Compiling source files...
echo.

REM 编译命令
"%MINGW_PATH%\g++.exe" -std=c++17 ^
    main.cpp ^
    Game.cpp ^
    Snake.cpp ^
    Food.cpp ^
    Renderer.cpp ^
    Input.cpp ^
    SaveSystem.cpp ^
    -I"D:\PATH\minggw\mingw64\include" ^
    -I"D:\PATH\sfml\include" ^
    -L"D:\PATH\minggw\mingw64\lib" ^
    -L"D:\PATH\sfml\lib" ^
    -o SnakeGame.exe ^
    -lgdi32 -luser32 ^
    -static-libgcc -static-libstdc++

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ====================================
    echo Build successful!
    echo ====================================
    echo You can run the game with: SnakeGame.exe
    echo.
) else (
    echo.
    echo ====================================
    echo Build failed!
    echo ====================================
    echo Please check the error messages above
)

pause
