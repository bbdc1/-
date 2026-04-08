#ifndef RENDERER_H
#define RENDERER_H

#include <windows.h>
#include <string>
#include <vector>

class Renderer {
public:
    Renderer();
    ~Renderer();

    // 初始化双缓冲
    void initialize();
    
    // 清空缓冲区
    void clear();
    
    // 在指定位置绘制字符
    void drawChar(int x, int y, char ch);
    
    // 在指定位置绘制字符串
    void drawString(int x, int y, const std::string& str);
    
    // 绘制蛇身
    void drawSnakeSegment(int x, int y, bool isHead);
    
    // 绘制食物
    void drawFood(int x, int y);
    
    // 绘制分数
    void drawScore(int score);
    
    // 绘制难度
    void drawDifficulty(const std::string& difficulty);
    
    // 绘制游戏状态信息
    void drawGameInfo(const std::string& status);
    
    // 交换缓冲区（显示到屏幕）
    void swapBuffer();
    
    // 获取控制台宽度
    int getWidth() const { return width; }
    
    // 获取控制台高度
    int getHeight() const { return height; }

private:
    HANDLE hConsole;
    HANDLE hBackBuffer;      // 后台缓冲区句柄
    CHAR_INFO* backBuffer;   // 后台缓冲区数据
    int width;
    int height;
    
    // 设置控制台颜色
    void setColor(WORD color);
};

#endif // RENDERER_H
