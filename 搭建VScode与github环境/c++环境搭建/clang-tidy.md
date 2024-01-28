# clang-tidy介绍

## 简介
clang-tidy 是 Clang 工具套件的一部分，用于进行静态代码分析，并提供一系列的代码检查和修复建议。它可以帮助开发者发现潜在的代码问题、改进代码质量和符合代码规范。

### 安装
```
sudo apt install clang
clang-tidy --version
```

### 主要特点：
1. 静态代码分析： clang-tidy 提供了一套静态代码分析工具，用于检测潜在的代码问题，包括潜在的错误、不规范的代码风格和性能问题。

2. 基于 Clang： 作为 Clang 工具套件的一部分，clang-tidy 利用 Clang 编译器的强大分析能力，能够深入理解 C、C++、Objective-C 等语言的代码。

3. 可配置的检查： 用户可以通过配置文件或命令行选项选择性地启用或禁用不同的检查器，以适应项目的需求。

4. 代码修复： clang-tidy 不仅仅是一个代码检查工具，还可以提供一些自动修复建议，帮助开发者自动修复一些简单的问题。

5. 插件体系： clang-tidy 允许用户编写自定义的检查器和修改器，以满足特定项目或行业的需求。

6. 与编译器集成： 可以与 Clang 编译器集成使用，使得在编译代码的同时进行静态代码分析。

### 使用方式：
1. 命令行使用： 使用 clang-tidy 的基本方式是在终端中运行命令。例如：
```
clang-tidy source.cpp
```
2. 与编译器一同使用： clang-tidy 可以与 Clang 编译器一同使用，通过添加 -T 选项，如：
```
clang++ -std=c++11 -Wall -T source.cpp
```
3. 自定义配置： 用户可以创建一个 [.clang-tidy](.clang-tidy) 配置文件，通过配置文件来定义检查器的启用或禁用，以及一些其他的配置选项。

4. 使用编辑器插件： 一些集成开发环境（IDE）或编辑器提供了 clang-tidy 的插件，例如 VSCode、CLion 等，使得开发者可以在编辑器中直接运行 clang-tidy。
vscode中的clang-tidy已经很长时间不更新了，目前都是在[clangd插件](../vscode下载与安装.md#cc相关)中一同使用。

5. 自动修复： 通过添加 -fix 选项，clang-tidy 可以尝试自动修复一些简单的问题。例如：
```
clang-tidy -fix source.cpp
```
clang-tidy 对于项目的代码质量管理和代码规范的遵循具有很大的帮助。它可以在早期发现并纠正潜在的问题，提高代码的可维护性和可读性。

### 文档
[clang-tidy参数文档](https://releases.llvm.org/6.0.0/tools/clang/tools/extra/docs/clang-tidy/checks/list.html)