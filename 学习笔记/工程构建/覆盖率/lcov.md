# lcov + gcov

## lcov简介
lcov 是一个 Linux 平台上的代码覆盖率统计工具，基于 gcov（GCC 内置的覆盖率工具）进行扩展，可以将覆盖率数据生成 HTML 格式的可视化报告，便于开发者分析代码的测试覆盖情况。它支持多种覆盖率指标，包括函数覆盖率、代码行覆盖率和分支覆盖率。
LCOV 主要使用 Perl 语言编写，但也包含一些 Python 脚本。
## lcov 工作原理
### GCC 编译时添加覆盖率标志
使用 -fprofile-arcs 和 -ftest-coverage 编译代码，生成覆盖率数据文件（.gcda 和 .gcno）。

### 收集覆盖率数据
lcov 通过读取生成的 .gcda 文件，解析出覆盖率信息，生成中间格式文件（.info）。

### 生成覆盖率报告
通过 lcov 提供的 genhtml 工具，将 .info 文件转化为 HTML 格式的报告。


## 项目使用的关键技术和框架
### 关键技术
- GCOV: 用于收集代码覆盖率数据的基础工具。
- Perl: 主要用于实现 LCOV 的核心功能。
- Python: 用于一些辅助脚本和工具。
### 框架
- HTML: 用于生成可视化的覆盖率报告。
- JSON: 用于数据处理和交换。

## 版本信息

| lcov 版本 | 推荐的 GCC 版本 | 兼容情况 |
|----------|----------|----------|
| lcov 1.14    | GCC 4.5 ~ 9.0   | 官方支持，完全兼容   |
| lcov 1.15   | GCC 10.x   | 部分兼容，需要调整配置   |
| lcov 1.16+   | GCC 13.x 及以上   | 完美兼容，推荐使用   |

gcov 版本要兼容gcc/g++版本，如
```
$ gcov --version

gcov (Ubuntu 13.1.0-8ubuntu1~22.04) 13.1.0
$ g++ --version

g++ (Ubuntu 13.1.0-8ubuntu1~22.04) 13.1.0
$ gcc --version

gcc (Ubuntu 13.1.0-8ubuntu1~22.04) 13.1.0
```

## lcov 的安装
在大多数 Linux 发行版上，可以通过包管理器安装 lcov：
### Ubuntu/Debian
```
sudo apt-get install lcov
```
### Red Hat/CentOS
```
sudo yum install lcov
```

### 手动安装/升级lcov
可以下载源码进行手动安装

#### 准备工作
在安装 LCOV 之前，请确保您的系统满足以下要求：

- 安装了 Perl 5.10 或更高版本。
- 安装了 Python 3.7 或更高版本。
- 安装了 GCC 或 LLVM 编译器。
- 安装了必要的 Perl 模块，如 Capture::Tiny, DateTime, Devel::Cover, Digest::MD5, File::Spec, JSON::XS, Cpanel::JSON::XS, JSON::PP, JSON, Memory::Process, Module::Load::Conditional, Scalar::Util, Time::HiRes
#### 卸载之前版本
```
sudo apt remove lcov
```
#### 获取lcov
下载git工程
```
git clone git@github.com:linux-test-project/lcov.git
```
或者下载安装包
```
wget https://github.com/linux-test-project/lcov/releases/download/v2.2/lcov-2.2.tar.gz
tar -xvf lcov-2.2.tar.gz
```

#### 编译安装
- 进入目录
```
cd lcov
```
- 编译安装
```
make install
```
默认情况下，LCOV 将被安装到 /usr/local 目录。如果您希望安装到其他目录，可以使用 PREFIX 变量指定安装路径：
```
make PREFIX=/your/custom/path install
```

- 检查是否安装成功
```
whereis lcov
lcov --version
```


#### 可能存在的问题
- 缺少perl中的某些模块， e.g.：
```
$ lcov --versiob

Can't locate Capture/Tiny.pm in @INC (you may need to install the Capture::Tiny module) ...
```
- 解决方案， 参考文档[perl.md](./perl.md#安装缺少的模块)
1. 使用cpan/cpanminus进行安装
2. 去meta::cpan网站上下载对应的模块，进行编译安装

### 使用
#### c工程
使用[示例中的c工程](./示例/c/)为例
- 启用`--coverage`进行编译
```
$ gcc --coverage -g -c main.c math_utils.c
$ gcc --coverage -o app main.o math_utils.o
```

- 执行和输出
```
$ ./app

Addition: 5 + 3 = 8
Subtraction: 5 - 3 = 2
```
此时，会生成 .gcno 和 .gcda 文件：
```
main.gcno  main.gcda  math_utils.gcno  math_utils.gcda
```
- 使用`lcov`捕获覆盖率数据
```
lcov --capture --directory . --output-file coverage.info
```
此时会生产`coverage.info`文件

- 生成`HTML`报告
```
genhtml coverage.info --output-directory coverage-report
```
在`coverage-report`中的html文件就是覆盖率报告

- 清理
```
find . -name "*.gcda" -o -name "*.gcno" -o -name "coverage.info" -o -name "coverage-report" | xargs rm -rf
```

#### c++工程
使用[示例中的c++工程](./示例/c++/)为例
- 启用`--coverage`进行编译
```
$ g++ --coverage -g -c main.cpp math_utils.cpp
$ g++ --coverage -o app main.o math_utils.o
```

- 执行和输出
```
$ ./app

Addition: 5 + 3 = 8
Subtraction: 5 - 3 = 2
```
此时，会生成 .gcno 和 .gcda 文件：
```
main.gcno  main.gcda  math_utils.gcno  math_utils.gcda
```
- 使用`lcov`捕获覆盖率数据
```
lcov --capture --directory . --output-file coverage.info
```
此时会生产`coverage.info`文件

- 生成`HTML`报告
```
genhtml coverage.info --output-directory coverage-report
```
在`coverage-report`中的html文件就是覆盖率报告

- 清理
```
find . -name "*.gcda" -o -name "*.gcno" -o -name "coverage.info" -o -name "coverage-report" | xargs rm -rf
```

#### makefile工程

- 编译项目并运行测试
```
$ make coverage
```

- 清理
```
find . -name "*.gcda" -o -name "*.gcno" -o -name "coverage.info" -o -name "coverage-report" | xargs rm -rf
```

#### cmake工程

- 编译项目并运行测试
```
chmod +x run_coverage.sh
./run_coverage.sh
```

- 清理

确保在CMakeLists.txt文件中添加
```
add_custom_target(clean_coverage
    COMMAND find . -name "*.gcda" -o -name "*.gcno" -o -name "coverage.info" -o -name "coverage-report" | xargs rm -rf
)
```
之后重新执行run_coverage.sh脚本

```
cd build
make clean_coverage
```