#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include "Snake.h"
#include "Food.h"
#include <string>
#include <fstream>

struct GameState {
    std::string snakeData;      // 蛇的序列化数据
    std::string foodData;       // 食物的序列化数据
    int score;                  // 当前分数
    bool isPaused;              // 是否暂停
    bool isGameOver;            // 游戏是否结束
};

class SaveSystem {
public:
    SaveSystem();
    
    // 保存游戏到文件（JSON 格式）
    bool saveGame(const std::string& filename, const GameState& state);
    
    // 从文件加载游戏
    GameState loadGame(const std::string& filename);
    
    // 检查存档文件是否存在
    bool hasSaveFile(const std::string& filename) const;
    
    // 获取最后错误信息
    std::string getLastError() const;

private:
    std::string lastError;
    
    // 辅助函数：读取整个文件内容
    std::string readFile(const std::string& filename) const;
    
    // 辅助函数：写入文件
    bool writeFile(const std::string& filename, const std::string& content) const;
    
    // 简单的 JSON 解析辅助
    std::string parseJsonValue(const std::string& json, const std::string& key) const;
    int parseJsonInt(const std::string& json, const std::string& key) const;
    bool parseJsonBool(const std::string& json, const std::string& key) const;
};

#endif // SAVESYSTEM_H
