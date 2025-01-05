#!/bin/bash

# 清理旧的构建目录
rm -rf build coverage.info coverage-report

# 创建构建目录并切换到该目录
mkdir build
cd build

# 配置 CMake 工程，使用 Coverage 模式
cmake -DCMAKE_C_COMPILER=gcc-13 -DCMAKE_CXX_COMPILER=g++-13 -DCMAKE_BUILD_TYPE=Coverage ..

# 编译工程
make

# 运行可执行文件
./coverage-example

# 生成覆盖率数据
lcov --capture --directory . --output-file coverage.info

# 过滤掉不必要的系统文件
lcov --remove coverage.info '/usr/*' --output-file coverage.info

# 生成 HTML 报告
genhtml coverage.info --output-directory coverage-report

# 打印报告路径
echo "Coverage report generated in build/coverage-report/index.html"
