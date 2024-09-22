# 内容

本文件夹下记录在日常学习与工作中见到的代码段

# 代码段要求

- 为了快速迁移与方便验证，每个代码片段默认能够在 linux 环境下使用 vscode cmake 工具进行编译与执行，如果因为依赖过多而无法编译，需要进行标注
- 默认使用 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17") 使用 c++17 进行编译
- 搭建 linux + vscode + cmake 编译调试的环境可以参考https://blog.csdn.net/Tengfei_Y/article/details/126893402
- 如果有复杂的工程需要编译，希望额外生成 cmake 工程进行编写，简单的工程只需要在 CMakeLists.txt 中替换需要编译测试的文件名称即可
- 因为是用于日常积累的代码段，需要在记录时标注出处，便于归纳总结时候快速的知道来源与用途
