#include "SaveSystem.h"
#include <sstream>

SaveSystem::SaveSystem() : lastError("") {
}

bool SaveSystem::saveGame(const std::string& filename, const GameState& state) {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        lastError = "无法打开文件进行写入：" + filename;
        return false;
    }
    
    // 使用 JSON 格式保存
    file << "{\n";
    file << "  \"snake\": \"" << state.snakeData << "\",\n";
    file << "  \"food\": \"" << state.foodData << "\",\n";
    file << "  \"score\": " << state.score << ",\n";
    file << "  \"isPaused\": " << (state.isPaused ? "true" : "false") << ",\n";
    file << "  \"isGameOver\": " << (state.isGameOver ? "true" : "false") << "\n";
    file << "}\n";
    
    file.close();
    return true;
}

GameState SaveSystem::loadGame(const std::string& filename) {
    GameState state;
    state.score = 0;
    state.isPaused = false;
    state.isGameOver = false;
    
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        lastError = "无法打开文件进行读取：" + filename;
        return state;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file.close();
    
    // 解析 JSON
    state.snakeData = parseJsonValue(content, "snake");
    state.foodData = parseJsonValue(content, "food");
    state.score = parseJsonInt(content, "score");
    state.isPaused = parseJsonBool(content, "isPaused");
    state.isGameOver = parseJsonBool(content, "isGameOver");
    
    return state;
}

bool SaveSystem::hasSaveFile(const std::string& filename) const {
    std::ifstream file(filename);
    return file.good();
}

std::string SaveSystem::getLastError() const {
    return lastError;
}

std::string SaveSystem::readFile(const std::string& filename) const {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    
    return buffer.str();
}

bool SaveSystem::writeFile(const std::string& filename, const std::string& content) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    file << content;
    file.close();
    return true;
}

std::string SaveSystem::parseJsonValue(const std::string& json, const std::string& key) const {
    std::string searchKey = "\"" + key + "\"";
    size_t keyPos = json.find(searchKey);
    
    if (keyPos == std::string::npos) {
        return "";
    }
    
    size_t colonPos = json.find(':', keyPos);
    if (colonPos == std::string::npos) {
        return "";
    }
    
    size_t startQuote = json.find('"', colonPos);
    if (startQuote == std::string::npos) {
        return "";
    }
    
    size_t endQuote = json.find('"', startQuote + 1);
    if (endQuote == std::string::npos) {
        return "";
    }
    
    return json.substr(startQuote + 1, endQuote - startQuote - 1);
}

int SaveSystem::parseJsonInt(const std::string& json, const std::string& key) const {
    std::string searchKey = "\"" + key + "\"";
    size_t keyPos = json.find(searchKey);
    
    if (keyPos == std::string::npos) {
        return 0;
    }
    
    size_t colonPos = json.find(':', keyPos);
    if (colonPos == std::string::npos) {
        return 0;
    }
    
    size_t valueStart = colonPos + 1;
    while (valueStart < json.length() && (json[valueStart] == ' ' || json[valueStart] == '\t')) {
        valueStart++;
    }
    
    size_t valueEnd = valueStart;
    while (valueEnd < json.length() && (isdigit(json[valueEnd]) || json[valueEnd] == '-')) {
        valueEnd++;
    }
    
    try {
        return std::stoi(json.substr(valueStart, valueEnd - valueStart));
    } catch (...) {
        return 0;
    }
}

bool SaveSystem::parseJsonBool(const std::string& json, const std::string& key) const {
    std::string searchKey = "\"" + key + "\"";
    size_t keyPos = json.find(searchKey);
    
    if (keyPos == std::string::npos) {
        return false;
    }
    
    size_t colonPos = json.find(':', keyPos);
    if (colonPos == std::string::npos) {
        return false;
    }
    
    size_t valueStart = colonPos + 1;
    while (valueStart < json.length() && (json[valueStart] == ' ' || json[valueStart] == '\t')) {
        valueStart++;
    }
    
    if (json.substr(valueStart, 4) == "true") {
        return true;
    }
    
    return false;
}
