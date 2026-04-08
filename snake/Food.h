#ifndef FOOD_H
#define FOOD_H

#include "Snake.h"
#include <cstdlib>
#include <ctime>

class Food {
public:
    Food();
    
    // 生成新食物位置
    void spawn(const std::vector<Position>& snakeBody, int wallWidth, int wallHeight);
    
    // 获取食物位置
    Position getPosition() const;
    
    // 设置食物位置
    void setPosition(int x, int y);
    
    // 序列化数据（用于存档）
    std::string serialize() const;
    
    // 反序列化数据（用于读档）
    void deserialize(const std::string& data);

private:
    Position position;
    
    // 检查位置是否在蛇身上
    bool isOnSnake(const Position& pos, const std::vector<Position>& snakeBody) const;
};

#endif // FOOD_H
