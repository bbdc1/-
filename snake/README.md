# 贪吃蛇游戏 (Snake Game)

一个使用 C++ 和 Windows API 开发的控制台贪吃蛇游戏。

## ✅ 已完成功能

### （1）基础功能（60%）
- ✅ **控制台界面渲染（双缓冲）** - 使用 Windows API 的 CHAR_INFO 缓冲区实现无闪烁渲染
- ✅ **贪吃蛇基本机制**
  - ✅ 移动 - 蛇可以上下左右移动
  - ✅ 吃食物增长 - 吃到食物后蛇身增长
  - ✅ 碰撞检测 - 墙体碰撞和自身碰撞检测
  - ✅ 键盘输入控制 - 方向键控制，Q 键退出
- ✅ **分数系统** - 每吃一个食物得 10 分

### （2）进阶功能（30%）
- ✅ **存档/读档系统**
  - ✅ 支持保存：蛇身位置、当前方向、食物位置、分数
  - ✅ 存储格式：JSON 文本文件（.json）
- ✅ **游戏状态管理**
  - ✅ 开始 / 暂停 / 结束
  - ✅ 可从存档恢复

### （3）工程规范（10%）
- ✅ **清晰的项目结构**
```
SnakeGame/
│── main.cpp                    # 程序入口
│── Game.h / Game.cpp           # 游戏主逻辑和状态管理
│── Snake.h / Snake.cpp         # 蛇的移动和增长机制
│── Food.h / Food.cpp           # 食物生成和碰撞检测
│── Renderer.h / Renderer.cpp   # 双缓冲控制台渲染
│── Input.h / Input.cpp         # 键盘输入控制
│── SaveSystem.h / SaveSystem.cpp # 存档/读档系统
│── CMakeLists.txt              # CMake 构建配置
│── build.bat                   # Windows 编译脚本
└── README.md                   # 说明文档
```

## 🎮 操作说明

| 按键 | 功能 |
|------|------|
| ↑ ↓ ← → | 控制蛇的移动方向 |
| P | 暂停/继续游戏 |
| S | 保存游戏进度 |
| L | 读取存档 |
| Q | 退出游戏 |

## 🚀 编译方法

### 使用 MinGW 编译器
项目已经成功编译生成 `SnakeGame.exe`

如果需要重新编译，运行：
```bash
D:\PATH\minggw\mingw64\bin\g++.exe -std=c++17 main.cpp Game.cpp Snake.cpp Food.cpp Renderer.cpp Input.cpp SaveSystem.cpp -I"D:\PATH\minggw\mingw64\include" -L"D:\PATH\minggw\mingw64\lib" -o SnakeGame.exe -lgdi32 -luser32 -static-libgcc -static-libstdc++
```

## 🎯 运行游戏

双击 `SnakeGame.exe` 或命令行运行：
```bash
.\SnakeGame.exe
```

## 📖 游戏规则

1. 使用方向键控制蛇的移动方向
2. 吃到食物（显示为 `*`）得 10 分，蛇身变长一节
3. 撞到墙壁（`=` 或 `|`）或自己的身体则游戏结束
4. 蛇头用 `O` 表示，身体用 `o` 表示
5. 游戏区域大小：60x20

## 💾 存档系统

- **存档文件格式**：JSON
- **存档文件名**：`savegame.json`
- **保存内容**：
  - 蛇的所有身体段位置
  - 蛇的当前移动方向
  - 食物的当前位置
  - 当前分数
  - 游戏状态（运行/暂停）

### 示例存档文件
```json
{
  "snake": "3;10,10;9,10;8,10",
  "food": "15,12",
  "score": 50,
  "isPaused": false,
  "isGameOver": false
}
```

## 🛠️ 技术特性

- **双缓冲渲染**：使用 Windows API 的 `WriteConsoleOutputA` 实现后台缓冲，避免屏幕闪烁
- **固定时间步长更新**：游戏逻辑以固定间隔（150ms）更新，保证游戏体验一致
- **输入缓冲处理**：防止快速反向移动导致的自杀行为
- **随机食物生成**：确保食物不会生成在蛇身上

## ⚙️ 依赖库

- MinGW GCC (D:\PATH\minggw\mingw64)
- Windows API (user32.lib, gdi32.lib)

---

**开发完成时间**：2026 年 3 月 31 日  
**编译器**：MinGW GCC 17  
**平台**：Windows
