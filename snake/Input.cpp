#include "Input.h"
#include <conio.h>

Input::Input() {
}

bool Input::hasInput() const {
    return _kbhit();
}

Direction Input::readDirectionKey() {
    if (!_kbhit()) {
        return Direction::UP;  // NONE用UP表示无效
    }
    
    int key = _getch();
    
    // 处理方向键（需要先读取0xE0前缀）
    if (key == 0 || key == 0xE0) {
        key = _getch();  // 读取第二个字节
        
        switch (key) {
            case 72: return Direction::UP;
            case 80: return Direction::DOWN;
            case 75: return Direction::LEFT;
            case 77: return Direction::RIGHT;
        }
    }
    
    // 处理WASD键
    switch (key) {
        case 'w': case 'W': return Direction::UP;
        case 's': case 'S': return Direction::DOWN;
        case 'a': case 'A': return Direction::LEFT;
        case 'd': case 'D': return Direction::RIGHT;
    }
    
    return Direction::UP;  // 无效输入
}

KeyAction Input::readActionKey() {
    if (!_kbhit()) {
        return KeyAction::NONE;
    }
    
    int key = _getch();
    
    // 跳过方向键前缀
    if (key == 0 || key == 0xE0) {
        _getch();  // 消费第二个字节
        return KeyAction::NONE;
    }
    
    // 处理功能键
    switch (key) {
        case 'p': case 'P': return KeyAction::PAUSE;
        case 'q': case 'Q': return KeyAction::QUIT;
        case 's': case 'S': return KeyAction::SAVE;
        case 'l': case 'L': return KeyAction::LOAD;
        case 'd': case 'D': return KeyAction::DIFFICULTY;
    }
    
    return KeyAction::NONE;
}

// 【核心实现】最新合法输入覆盖策略
Direction Input::processInput(Direction currentDirection) {
    Direction latestValidDir = currentDirection;
    
    // 读取同一帧内的所有输入
    while (_kbhit()) {
        Direction input = readDirectionKey();
        
        // 跳过无效输入
        if (input == Direction::UP && _kbhit() == false) {
            // 检查是否是真的UP还是无效输入
            break;
        }
        
        // 关键：过滤180°反向输入
        if (!isOpposite(input, currentDirection)) {
            latestValidDir = input;  // 最新合法输入覆盖
        }
        // 如果是反向输入，直接忽略（防止自撞）
    }
    
    return latestValidDir;
}

KeyAction Input::getActionInput() {
    if (!_kbhit()) {
        return KeyAction::NONE;
    }
    
    int key = _getch();
    
    // 处理方向键前缀
    if (key == 0 || key == 0xE0) {
        key = _getch();
        return KeyAction::NONE;  // 方向键不是功能键
    }
    
    // 处理功能键
    switch (key) {
        case 'p': case 'P': return KeyAction::PAUSE;
        case 'q': case 'Q': return KeyAction::QUIT;
        case 's': case 'S': return KeyAction::SAVE;
        case 'l': case 'L': return KeyAction::LOAD;
        case 'd': case 'D': return KeyAction::DIFFICULTY;
    }
    
    return KeyAction::NONE;
}
