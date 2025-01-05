cmake_minimum_required(VERSION 3.16)
project(CoverageExample CXX)

# 如果是 Coverage 构建类型，则启用覆盖率编译选项
if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
    message(STATUS "Building with coverage support")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
endif()

add_custom_target(clean_coverage
    COMMAND find . -name "*.gcda" -o -name "*.gcno" -o -name "coverage.info" -o -name "coverage-report" | xargs rm -rf
)

# 设置源文件和头文件目录
include_directories(include)

# 添加可执行文件
add_executable(coverage-example src/main.cpp src/math_utils.cpp)

