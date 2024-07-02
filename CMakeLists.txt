cmake_minimum_required(VERSION 3.27)
project(Dad_n_Me)

set(CMAKE_CXX_STANDARD 17)

# 添加一个包含目录的变量
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

# 包含所有头文件的目录
include_directories(${INCLUDE_DIR})

# 收集所有源文件
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)

#link_libraries(libeasyx.a libgdi32.a libole32.a)
link_libraries(libeasyx.a)


add_executable(Dad_n_Me Top_game.cpp ${SOURCES})
