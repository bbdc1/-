#include "Renderer.h"
#include <iostream>

Renderer::Renderer() : hConsole(nullptr), hBackBuffer(nullptr), 
                        backBuffer(nullptr), width(80), height(25) {
}

Renderer::~Renderer() {
    if (backBuffer) {
        delete[] backBuffer;
    }
    if (hBackBuffer) {
        CloseHandle(hBackBuffer);
    }
}

void Renderer::initialize() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // 隐藏光标
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    
    // 设置控制台大小
    SMALL_RECT consoleSize;
    consoleSize.Left = 0;
    consoleSize.Top = 0;
    consoleSize.Right = width - 1;
    consoleSize.Bottom = height - 1;
    
    SetConsoleWindowInfo(hConsole, TRUE, &consoleSize);
    
    // 创建后台缓冲区
    COORD bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
    backBuffer = new CHAR_INFO[width * height];
    
    // 初始化后台缓冲区
    for (int i = 0; i < width * height; ++i) {
        backBuffer[i].Char.AsciiChar = ' ';
        backBuffer[i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    }
}

void Renderer::clear() {
    for (int i = 0; i < width * height; ++i) {
        backBuffer[i].Char.AsciiChar = ' ';
        backBuffer[i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    }
}

void Renderer::drawChar(int x, int y, char ch) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        int index = y * width + x;
        backBuffer[index].Char.AsciiChar = ch;
        backBuffer[index].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    }
}

void Renderer::drawString(int x, int y, const std::string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (x + static_cast<int>(i) < width) {
            drawChar(x + static_cast<int>(i), y, str[i]);
        }
    }
}

void Renderer::setColor(WORD color) {
    // 颜色设置辅助函数
}

void Renderer::drawSnakeSegment(int x, int y, bool isHead) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        int index = y * width + x;
        backBuffer[index].Char.AsciiChar = isHead ? 'O' : 'o';
        if (isHead) {
            backBuffer[index].Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        } else {
            backBuffer[index].Attributes = FOREGROUND_GREEN;
        }
    }
}

void Renderer::drawFood(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        int index = y * width + x;
        backBuffer[index].Char.AsciiChar = '*';
        backBuffer[index].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
    }
}

void Renderer::drawScore(int score) {
    std::string scoreText = "Score: " + std::to_string(score);
    drawString(2, height - 2, scoreText);
}

void Renderer::drawDifficulty(const std::string& difficulty) {
    std::string diffText = "Difficulty: " + difficulty;
    drawString(width / 2 - 10, height - 2, diffText);
}

void Renderer::drawGameInfo(const std::string& status) {
    drawString(2, height - 3, status);
    drawString(2, height - 1, "Controls: Arrows=Move P=Pause D=Difficulty S=Save L=Load Q=Quit");
}

void Renderer::swapBuffer() {
    // 将后台缓冲区内容写入控制台
    SMALL_RECT writeRegion;
    writeRegion.Left = 0;
    writeRegion.Top = 0;
    writeRegion.Right = width - 1;
    writeRegion.Bottom = height - 1;
    
    COORD bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
    COORD bufferCoord = { 0, 0 };
    
    WriteConsoleOutputA(hConsole, backBuffer, bufferSize, bufferCoord, &writeRegion);
}
