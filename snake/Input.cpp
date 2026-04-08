#include "Input.h"
#include <conio.h>

Input::Input() : lastKey(0) {
}

bool Input::hasInput() const {
    return _kbhit();
}

KeyAction Input::getKeyInput() {
    if (_kbhit()) {
        int key = _getch();
        
        // 处理方向键（需要先读取 0xE0 前缀）
        if (key == 0 || key == 0xE0) {
            key = _getch();  // 读取第二个字节
            
            switch (key) {
                case 72:  // 上箭头
                    return KeyAction::UP;
                case 80:  // 下箭头
                    return KeyAction::DOWN;
                case 75:  // 左箭头
                    return KeyAction::LEFT;
                case 77:  // 右箭头
                    return KeyAction::RIGHT;
            }
        } else {
            // 处理普通按键
            switch (key) {
                case 'p':
                case 'P':
                    return KeyAction::PAUSE;
                case 'q':
                case 'Q':
                    return KeyAction::QUIT;
                case 's':
                case 'S':
                    return KeyAction::SAVE;
                case 'l':
                case 'L':
                    return KeyAction::LOAD;
                case 'd':
                case 'D':
                    return KeyAction::DIFFICULTY;
            }
        }
    }
    
    return KeyAction::NONE;
}
