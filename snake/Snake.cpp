#include "Snake.h"
#include <sstream>
#include <stdexcept>

Snake::Snake(int startX, int startY) : currentDirection(Direction::RIGHT), 
                                        nextDirection(Direction::RIGHT),
                                        shouldGrow(false) {
    // 初始化蛇身，包含 3 节
    body.push_back({startX, startY});
    body.push_back({startX - 1, startY});
    body.push_back({startX - 2, startY});
}

void Snake::move() {
    // 更新实际方向
    currentDirection = nextDirection;
    
    // 计算新的蛇头位置
    Position newHead = body.front();
    
    switch (currentDirection) {
        case Direction::UP:
            newHead.y -= 1;
            break;
        case Direction::DOWN:
            newHead.y += 1;
            break;
        case Direction::LEFT:
            newHead.x -= 1;
            break;
        case Direction::RIGHT:
            newHead.x += 1;
            break;
    }
    
    // 将新头部加入身体前端
    body.insert(body.begin(), newHead);
    
    // 如果不需要增长，则移除尾部
    if (!shouldGrow) {
        body.pop_back();
    } else {
        shouldGrow = false;  // 重置增长标志
    }
}

void Snake::grow() {
    shouldGrow = true;
}

void Snake::changeDirection(Direction newDir) {
    // 防止直接反向移动（使用isOpposite函数）
    if (!isOpposite(newDir, currentDirection)) {
        nextDirection = newDir;
    }
}

void Snake::updateDirection(Direction newDir) {
    // 最新合法输入覆盖策略
    // 同一帧内允许多次调用，只保留最后一个合法方向
    if (!isOpposite(newDir, currentDirection)) {
        nextDirection = newDir;  // 覆盖之前的输入
    }
    // 如果是反向输入，直接忽略（防止180°自撞）
}

bool Snake::checkCollision(int wallWidth, int wallHeight) const {
    Position head = body.front();
    
    // 检测墙体碰撞
    if (head.x < 0 || head.x >= wallWidth || head.y < 0 || head.y >= wallHeight) {
        return true;
    }
    
    // 检测自身碰撞（从第二节开始）
    for (size_t i = 1; i < body.size(); ++i) {
        if (body[i] == head) {
            return true;
        }
    }
    
    return false;
}

bool Snake::checkFoodCollision(const Position& foodPos) const {
    return body.front() == foodPos;
}

Position Snake::getHeadPosition() const {
    return body.front();
}

const std::vector<Position>& Snake::getBody() const {
    return body;
}

Direction Snake::getDirection() const {
    return currentDirection;
}

void Snake::reset(int startX, int startY) {
    body.clear();
    body.push_back({startX, startY});
    body.push_back({startX - 1, startY});
    body.push_back({startX - 2, startY});
    currentDirection = Direction::RIGHT;
    nextDirection = Direction::RIGHT;
    shouldGrow = false;
}

std::string Snake::serialize() const {
    std::stringstream ss;
    
    // 格式：direction;x1,y1;x2,y2;x3,y3;...
    ss << static_cast<int>(currentDirection);
    for (const auto& segment : body) {
        ss << ";" << segment.x << "," << segment.y;
    }
    
    return ss.str();
}

void Snake::deserialize(const std::string& data) {
    body.clear();
    
    std::stringstream ss(data);
    std::string token;
    
    // 读取方向
    if (std::getline(ss, token, ';')) {
        int dir = std::stoi(token);
        currentDirection = static_cast<Direction>(dir);
        nextDirection = currentDirection;
    }
    
    // 读取蛇身各段
    while (std::getline(ss, token, ';')) {
        size_t commaPos = token.find(',');
        if (commaPos != std::string::npos) {
            int x = std::stoi(token.substr(0, commaPos));
            int y = std::stoi(token.substr(commaPos + 1));
            body.push_back({x, y});
        }
    }
}
