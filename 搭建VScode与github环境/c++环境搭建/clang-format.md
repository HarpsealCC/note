# clang-format介绍

## 介绍
clang-format 是一个由 Clang 工具套件提供的工具，用于格式化 C、C++、Objective-C、和 JavaScript/TypeScript 代码。它可以帮助团队在项目中维持一致的代码风格，提高代码的可读性。

以下是一些 clang-format 的主要特点和使用方式：

### 主要特点：
自动代码格式化： clang-format 能够根据指定的代码样式规则自动格式化源代码。

高度可配置： 用户可以通过配置文件或命令行参数定制代码样式，包括缩进、换行、括号的位置等。

支持多种编程语言： 主要用于 C、C++、Objective-C，但也提供了对 JavaScript 和 TypeScript 的支持。

与 Clang 兼容： clang-format 是 Clang 工具套件的一部分，与 Clang 编译器兼容。

### 使用方式：
- 命令行：

在终端中使用命令行执行 clang-format。例如：
```
clang-format -style=Google -i myfile.cpp
```
这会按照 Google 风格格式化 myfile.cpp 文件。
### 配置文件：

可以在项目中添加一个 [.clang-format](.clang-format) 配置文件，指定代码样式。配置文件可以包含多个样式选项，也可以继承现有样式。

### 集成到编辑器中：

clang-format 可以集成到一些编辑器中，如 VSCode、Sublime Text，以便在编辑器中直接格式化代码。在 VSCode 中，可以使用 ["Clang-Format" 扩展](../vscode下载与安装.md#cc相关)来实现。
### 与版本控制系统集成：

可以将 clang-format 与版本控制系统集成，例如 Git 钩子，以确保提交的代码符合团队的代码风格。
### 样式选择：

clang-format 支持多种预定义的代码样式，如 Google、LLVM、WebKit 等。用户也可以创建自定义样式。
### 查看帮助：

在终端中运行 clang-format -help 可以查看 clang-format 的详细帮助信息，了解所有可用的配置选项。
clang-format 在大型项目和团队中很有用，因为它可以帮助保持一致的代码风格，减少代码审查时的争议，提高代码的可维护性。

### 文档
[官方文档](https://clang.llvm.org/docs/ClangFormatStyleOptions.html)
[clang format 官方文档自定义参数介绍（中英文）](https://www.cnblogs.com/PaulpauL/p/5929753.html)