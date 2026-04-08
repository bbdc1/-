#include "Game.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

int main() {
    // 设置控制台编码为 UTF-8
    SetConsoleOutputCP(CP_UTF8);
    
    std::cout << "=====================================" << std::endl;
    std::cout << "         Welcome to Snake Game       " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  Arrow Keys - Move the snake" << std::endl;
    std::cout << "  P - Pause/Resume game" << std::endl;
    std::cout << "  S - Save game" << std::endl;
    std::cout << "  L - Load game" << std::endl;
    std::cout << "  Q - Quit game" << std::endl;
    std::cout << std::endl;
    std::cout << "Press any key to start..." << std::endl;
    
    // 等待按键开始
    _getch();
    
    // 创建并初始化游戏
    Game game;
    if (!game.initialize()) {
        std::cerr << "Failed to initialize game!" << std::endl;
        return 1;
    }
    
    // 运行游戏
    game.run();
    
    std::cout << std::endl;
    std::cout << "Thanks for playing!" << std::endl;
    
    return 0;
}
