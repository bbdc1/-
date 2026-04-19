#ifndef INPUT_H
#define INPUT_H

#include "Snake.h"
#include <windows.h>

enum class KeyAction {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    PAUSE,
    QUIT,
    SAVE,
    LOAD,
    DIFFICULTY
};

class Input {
public:
    Input();
    
    // 【核心】最新合法输入覆盖策略
    // 同一帧内读取所有输入，只保留最后一个合法方向
    Direction processInput(Direction currentDirection);
    
    // 获取功能键输入（暂停、退出等）
    KeyAction getActionInput();
    
    // 检查是否有输入
    bool hasInput() const;

private:
    // 读取单个按键
    Direction readDirectionKey();
    KeyAction readActionKey();
};

#endif // INPUT_H
