#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <string>

struct Position {
    int x;
    int y;
    
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake {
public:
    Snake(int startX, int startY);
    
    // 移动蛇
    void move();
    
    // 增长蛇身
    void grow();
    
    // 改变方向
    void changeDirection(Direction newDir);
    
    // 检测碰撞（墙体和自身）
    bool checkCollision(int wallWidth, int wallHeight) const;
    
    // 检测是否吃到食物
    bool checkFoodCollision(const Position& foodPos) const;
    
    // 获取蛇头位置
    Position getHeadPosition() const;
    
    // 获取蛇身
    const std::vector<Position>& getBody() const;
    
    // 获取当前方向
    Direction getDirection() const;
    
    // 设置初始位置
    void reset(int startX, int startY);
    
    // 序列化数据（用于存档）
    std::string serialize() const;
    
    // 反序列化数据（用于读档）
    void deserialize(const std::string& data);

private:
    std::vector<Position> body;      // 蛇身
    Direction currentDirection;       // 当前方向
    Direction nextDirection;          // 下一步的方向（防止快速反向）
    bool shouldGrow;                  // 是否需要增长
};

#endif // SNAKE_H
