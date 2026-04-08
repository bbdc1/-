#include "Game.h"
#include <iostream>
#include <chrono>
#include <thread>

Game::Game() : snake(nullptr), food(nullptr), score(0), 
               status(GameStatus::GAME_OVER), difficulty(Difficulty::NORMAL),
               wallWidth(60), wallHeight(20) {
}

Game::~Game() {
    if (snake) delete snake;
    if (food) delete food;
}

bool Game::initialize() {
    // 初始化渲染器
    renderer.initialize();
    
    // 创建蛇和食物
    reset();
    
    return true;
}

void Game::reset() {
    if (snake) delete snake;
    if (food) delete food;
    
    // 在地图中央创建蛇
    snake = new Snake(wallWidth / 2, wallHeight / 2);
    food = new Food();
    
    // 生成第一个食物
    food->spawn(snake->getBody(), wallWidth, wallHeight);
    
    score = 0;
    status = GameStatus::RUNNING;
}

void Game::run() {
    auto lastUpdate = std::chrono::steady_clock::now();
    
    while (true) {
        auto currentTime = std::chrono::steady_clock::now();
        
        // 处理输入（每帧都处理）
        handleInput();
        
        // 如果游戏结束，退出循环
        if (status == GameStatus::GAME_OVER) {
            render();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        }
        
        // 更新游戏状态（根据难度动态调整速度）
        int frameDelay = getGameSpeed();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastUpdate).count() >= frameDelay) {
            if (status == GameStatus::RUNNING) {
                update();
            }
            lastUpdate = currentTime;
        }
        
        // 渲染画面
        render();
        
        // 短暂延迟以减少 CPU 占用
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void Game::update() {
    // 移动蛇
    snake->move();
    
    // 检测是否吃到食物
    if (snake->checkFoodCollision(food->getPosition())) {
        snake->grow();
        score += 10;
        
        // 生成新食物
        food->spawn(snake->getBody(), wallWidth, wallHeight);
    }
    
    // 检测碰撞
    if (checkGameOver()) {
        status = GameStatus::GAME_OVER;
    }
}

void Game::render() {
    renderer.clear();
    
    // 绘制边界
    drawBorders();
    
    // 绘制蛇
    const auto& body = snake->getBody();
    for (size_t i = 0; i < body.size(); ++i) {
        renderer.drawSnakeSegment(body[i].x, body[i].y, i == 0);
    }
    
    // 绘制食物
    Position foodPos = food->getPosition();
    renderer.drawFood(foodPos.x, foodPos.y);
    
    // 绘制分数
    renderer.drawScore(score);
    
    // 绘制难度
    renderer.drawDifficulty(getDifficultyText());
    
    // 绘制游戏状态信息
    std::string statusText;
    switch (status) {
        case GameStatus::RUNNING:
            statusText = "Status: Running";
            break;
        case GameStatus::PAUSED:
            statusText = "Status: PAUSED (Press P to continue)";
            break;
        case GameStatus::GAME_OVER:
            statusText = "Game Over! Press Q to quit";
            break;
        default:
            statusText = "";
    }
    renderer.drawGameInfo(statusText);
    
    // 交换缓冲区显示
    renderer.swapBuffer();
}

void Game::handleInput() {
    KeyAction action = input.getKeyInput();
    
    switch (action) {
        case KeyAction::UP:
            if (status == GameStatus::RUNNING) {
                snake->changeDirection(Direction::UP);
            }
            break;
        case KeyAction::DOWN:
            if (status == GameStatus::RUNNING) {
                snake->changeDirection(Direction::DOWN);
            }
            break;
        case KeyAction::LEFT:
            if (status == GameStatus::RUNNING) {
                snake->changeDirection(Direction::LEFT);
            }
            break;
        case KeyAction::RIGHT:
            if (status == GameStatus::RUNNING) {
                snake->changeDirection(Direction::RIGHT);
            }
            break;
        case KeyAction::PAUSE:
            if (status == GameStatus::RUNNING) {
                status = GameStatus::PAUSED;
            } else if (status == GameStatus::PAUSED) {
                status = GameStatus::RUNNING;
            }
            break;
        case KeyAction::QUIT:
            status = GameStatus::GAME_OVER;
            break;
        case KeyAction::SAVE:
            if (status == GameStatus::RUNNING || status == GameStatus::PAUSED) {
                saveGame();
            }
            break;
        case KeyAction::LOAD:
            loadGame();
            break;
        case KeyAction::DIFFICULTY:
            if (status == GameStatus::RUNNING || status == GameStatus::PAUSED) {
                switchDifficulty();
            }
            break;
        default:
            break;
    }
}

void Game::saveGame() {
    GameState state;
    state.snakeData = snake->serialize();
    state.foodData = food->serialize();
    state.score = score;
    state.isPaused = (status == GameStatus::PAUSED);
    state.isGameOver = false;
    
    if (saveSystem.saveGame(saveFileName, state)) {
        // 可以添加保存成功的提示
    } else {
        // 可以添加保存失败的提示
    }
}

void Game::loadGame() {
    if (!saveSystem.hasSaveFile(saveFileName)) {
        return;
    }
    
    GameState state = saveSystem.loadGame(saveFileName);
    
    if (!state.snakeData.empty()) {
        snake->deserialize(state.snakeData);
        food->deserialize(state.foodData);
        score = state.score;
        status = state.isPaused ? GameStatus::PAUSED : GameStatus::RUNNING;
    }
}

void Game::drawBorders() {
    // 绘制上边界
    for (int x = 0; x < wallWidth; ++x) {
        renderer.drawChar(x, 0, '=');
    }
    
    // 绘制下边界
    for (int x = 0; x < wallWidth; ++x) {
        renderer.drawChar(x, wallHeight - 1, '=');
    }
    
    // 绘制左边界
    for (int y = 1; y < wallHeight - 1; ++y) {
        renderer.drawChar(0, y, '|');
    }
    
    // 绘制右边界
    for (int y = 1; y < wallHeight - 1; ++y) {
        renderer.drawChar(wallWidth - 1, y, '|');
    }
}

bool Game::checkGameOver() const {
    return snake->checkCollision(wallWidth, wallHeight - 1);
}

int Game::getGameSpeed() const {
    switch (difficulty) {
        case Difficulty::EASY:   return 200;
        case Difficulty::NORMAL: return 150;
        case Difficulty::HARD:   return 100;
        case Difficulty::HELL:   return 50;
        default: return 150;
    }
}

std::string Game::getDifficultyText() const {
    switch (difficulty) {
        case Difficulty::EASY:   return "EASY";
        case Difficulty::NORMAL: return "NORMAL";
        case Difficulty::HARD:   return "HARD";
        case Difficulty::HELL:   return "HELL";
        default: return "NORMAL";
    }
}

void Game::switchDifficulty() {
    // 循环切换难度：EASY -> NORMAL -> HARD -> HELL -> EASY
    switch (difficulty) {
        case Difficulty::EASY:
            difficulty = Difficulty::NORMAL;
            break;
        case Difficulty::NORMAL:
            difficulty = Difficulty::HARD;
            break;
        case Difficulty::HARD:
            difficulty = Difficulty::HELL;
            break;
        case Difficulty::HELL:
            difficulty = Difficulty::EASY;
            break;
    }
}
