# 设置最低 CMake 版本
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(MapGenerator)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 查找 OpenCV 包
find_package(OpenCV REQUIRED)

# 添加可执行文件
add_executable(map map.cpp)

# 链接 OpenCV 库
target_link_libraries(map ${OpenCV_LIBS})