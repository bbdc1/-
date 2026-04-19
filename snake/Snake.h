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

// 方向约束工具函数：判断两个方向是否相反（180°）
inline bool isOpposite(Direction dir1, Direction dir2) {
    return (dir1 == Direction::UP && dir2 == Direction::DOWN) ||
           (dir1 == Direction::DOWN && dir2 == Direction::UP) ||
           (dir1 == Direction::LEFT && dir2 == Direction::RIGHT) ||
           (dir1 == Direction::RIGHT && dir2 == Direction::LEFT);
}

class Snake {
public:
    Snake(int startX, int startY);
    
    // 移动蛇
    void move();
    
    // 增长蛇身
    void grow();
    
    // 改变方向（带约束校验）
    void changeDirection(Direction newDir);
    
    // 更新方向（最新合法输入覆盖策略）
    void updateDirection(Direction newDir);
    
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
