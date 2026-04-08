#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Food.h"
#include "Renderer.h"
#include "Input.h"
#include "SaveSystem.h"

enum class GameStatus {
    RUNNING,
    PAUSED,
    GAME_OVER,
    WON
};

enum class Difficulty {
    EASY,      // 简单 - 200ms
    NORMAL,    // 普通 - 150ms
    HARD,      // 困难 - 100ms
    HELL       // 地狱 - 50ms
};

class Game {
public:
    Game();
    ~Game();
    
    // 初始化游戏
    bool initialize();
    
    // 运行游戏主循环
    void run();
    
    // 更新游戏状态
    void update();
    
    // 渲染游戏画面
    void render();
    
    // 处理输入
    void handleInput();
    
    // 保存游戏
    void saveGame();
    
    // 加载游戏
    void loadGame();
    
    // 重置游戏
    void reset();

private:
    Snake* snake;
    Food* food;
    Renderer renderer;
    Input input;
    SaveSystem saveSystem;
    
    int score;
    GameStatus status;
    Difficulty difficulty;
    int wallWidth;
    int wallHeight;
    
    const std::string saveFileName = "savegame.json";
    
    // 获取游戏速度（根据难度）
    int getGameSpeed() const;
    
    // 获取难度字符串
    std::string getDifficultyText() const;
    
    // 切换难度
    void switchDifficulty();
    
    // 绘制游戏边界
    void drawBorders();
    
    // 检查游戏是否结束
    bool checkGameOver() const;
};

#endif // GAME_H
