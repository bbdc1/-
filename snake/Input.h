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
    
    // 获取键盘输入
    KeyAction getKeyInput();
    
    // 检查是否有输入
    bool hasInput() const;

private:
    int lastKey;
};

#endif // INPUT_H
