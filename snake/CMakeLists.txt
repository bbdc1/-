cmake_minimum_required(VERSION 3.10)
project(SnakeGame VERSION 1.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加自定义库路径
link_directories(D:/PATH)
link_directories(D:/PATH/minggw)
link_directories(D:/PATH/sfml)
include_directories(D:/PATH)
include_directories(D:/PATH/minggw/include)
include_directories(D:/PATH/sfml/include)

# Windows 特定配置
if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0600)
endif()

# 源文件
set(SOURCES
    main.cpp
    Game.cpp
    Snake.cpp
    Food.cpp
    Renderer.cpp
    Input.cpp
    SaveSystem.cpp
)

# 头文件
set(HEADERS
    Game.h
    Snake.h
    Food.h
    Renderer.h
    Input.h
    SaveSystem.h
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Windows 平台链接必要的库
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE user32 gdi32)
endif()

# 设置输出目录
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
