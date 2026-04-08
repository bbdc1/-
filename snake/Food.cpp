#include "Food.h"
#include <random>
#include <algorithm>

Food::Food() {
    position = {5, 5};
}

void Food::spawn(const std::vector<Position>& snakeBody, int wallWidth, int wallHeight) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, wallWidth - 1);
    std::uniform_int_distribution<> disY(0, wallHeight - 1);
    
    // 随机生成食物位置，确保不在蛇身上
    do {
        position.x = disX(gen);
        position.y = disY(gen);
    } while (isOnSnake(position, snakeBody));
}

bool Food::isOnSnake(const Position& pos, const std::vector<Position>& snakeBody) const {
    return std::find(snakeBody.begin(), snakeBody.end(), pos) != snakeBody.end();
}

Position Food::getPosition() const {
    return position;
}

void Food::setPosition(int x, int y) {
    position = {x, y};
}

std::string Food::serialize() const {
    return std::to_string(position.x) + "," + std::to_string(position.y);
}

void Food::deserialize(const std::string& data) {
    size_t commaPos = data.find(',');
    if (commaPos != std::string::npos) {
        position.x = std::stoi(data.substr(0, commaPos));
        position.y = std::stoi(data.substr(commaPos + 1));
    }
}
