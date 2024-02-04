# vscode 调试 c++配置

本文档介绍如何在 linux+vscode 环境中配置使用 debug 功能（ctrl+shift+D）调试程序

## 需要安装的环境或插件

### vscode

c/c++
Code Runner（可选）

### linux

gcc/g++ : sudo apt-get install gcc/g++/build-essential
gdb : sudo apt-get install gdb

## 搭建步骤

### 创建工程

当前以 formwork 为例，需要含有待调试的文件。

### 建立配置文件

接下来在该目录下建立文件夹.vscode，并在文件中新建文件 c_cpp_properties.json 和 launch.json

- c_cpp_properties.json
  此文件是**c/c++插件**所需要的，好像不用写这个文件也可以调试。。。。

```
ctrl+shift+p
输入
edit
选择c++ edit Configurations(json)
建立c_cpp_properties.json

在"includePath"中，
输入头文件的路径
```

- launch.json
  在调用 debug 功能时如果没有会自动生成一个初始文件，将下面的信息写入到文件中

```
需要的修改：
program：路径设置为为cmake make 编译的可执行程序；
cwd：设置为${workspaceFolder}
注释掉"preLaunchTask"，大概是因为不用预编译，已经用cmake make 编译完成了
```

```
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "g++ - Build and debug active file",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/bin/main",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            //"preLaunchTask": "C/C++: g++ build active file",
            "miDebuggerPath": "/usr/bin/gdb"
        }
    ]
}
```

- task.json（目前不需要配置）
  此文件可能是需要直接编译 cpp 文件，如果有编译成功的可执行文件用来调试，可以不用配置这个文件，如果调试 C++，将下面 command 配置成 g++。

```
{
    // See https://go.microsoft.com/fwlink/?LinkId=733558
    // for the documentation about the tasks.json format
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",   // 任务名称，与launch.json的preLaunchTask相对应
            "type": "shell",
            "command": "gcc",   // 要使用的编译器
            "args": [
                "${file}",
                "-o", // 指定输出文件名，不加该参数则默认输出a.exe，Linux下默认a.out
                "${fileDirname}/${fileBasenameNoExtension}",
                "-g", // 生成和调试有关的信息
                "-Wall", // 开启额外警告
            ], // 编译命令参数

            "group": {
                "kind": "build",
                "isDefault": true // 设为false可做到一个tasks.json配置多个编译指令，需要自己修改本文件
            },
            "presentation": {
                "echo": true,
                "reveal": "always", // 在“终端”中显示编译信息的策略，可以为always，silent，never。具体参见VSC的文档
                "focus": true, // 设为true后可以使执行task时焦点聚集在终端
                "panel": "new" // 不同的文件的编译信息共享一个终端面板
            },
            // Use the standard MS compiler pattern to detect errors, warnings and infos
            "problemMatcher": "$msCompile"
        }
    ]
}
```


# 使用clangd代替c/c++

## 需要安装的环境或插件

### vscode

[clangd](../vscode下载与安装.md#cc相关)
[lldb](../vscode下载与安装.md#cc相关)

### linux
#### 安装clang
```
sudo apt install llvm-dev  // 安装llvm开发套件
sudo apt install clang // 安装clang
```

#### lldb
一般插件中是自带了lldb，不过注意centos7需要更新glibc到2.18，如果怕影响系统稳定，可以自己下载glibc1.28，然后只更新vscode插件的lldb所链接的动态库，可以参考[如何使CodeLLDB在CentOS7下工作](https://gist.github.com/JaySon-Huang/63dcc6c011feb5bd6deb1ef0cf1a9b96)

如果希望手动安装可以在安装clang时一同安装

### 建立配置文件

- **launch.json**
  vscode的debug功能使用析此文件，理解上应该是用于配置lldb需要调用的一些参数，可以配置多组，这样可以实现同一个目录下可以调用多种工程的debug。但是clangd与c/c++不能用
```
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug c++ templates",
            "type": "lldb",
            "request": "launch",
            "program": "${workspaceFolder}/学习笔记/c++/c++_template/build/exe_${fileBasenameNoExtension}",
            "args": [],
            "cwd": "${workspaceFolder}",
            "preLaunchTask": "c++_template", // 前置任务，可以是你的编译任务的名称
        },
        {
            "name": "c++ offer ",
            "type": "lldb",
            "request": "launch",
            "program": "${workspaceFolder}/学习笔记/c++/代码片段/build/exe_${fileBasenameNoExtension}",
            "args": [],
            "cwd": "${workspaceFolder}",
            "preLaunchTask": "c++_offer", // 前置任务，可以是你的编译任务的名称
        }
    ]
}
```

**参数说明**
```
version： 配置文件版本，通常是 "0.2.0"。
configurations： 包含调试配置的数组。
name： 配置的显示名, 不可重复
type： 调试器的类型，例如 "cppdbg" 表示 C++ 调试器， "lldb" 表示lldb调试器
request： 调试请求类型，通常是 "launch" 表示启动调试, "attach"表示接管正在执行的程序
program： 指定要调试的可执行文件的路径。
args： 传递给程序的命令行参数。
stopAtEntry： 是否在程序入口处停止。
cwd： 调试器的当前工作目录。
environment： 环境变量的设置。
externalConsole： 是否在外部控制台中运行程序。
setupCommands： 在启动调试器之前执行的命令。
preLaunchTask： 在启动调试器之前运行的任务，一般配合tasks.json使用，填写其label
```

- **tasks.json**
  应该是配合launch.json一起使用的，用于在launch模式下对工程进行编译，应该还可以配合cmake与build.sh脚本进行使用
```
{
    "tasks": [
        {
            "label": "c++_template",
            "type": "process",
            "command": "clang++",
            "args": [
                "${file}",
                "-g",
                "-o",
                "${workspaceFolder}/学习笔记/c++/c++_template/build/exe_${fileBasenameNoExtension}", // 输出到build文件夹下
                "-Wall",
                "-std=c++17",
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "options": {
                "cwd": "${fileDirname}"
            },
        },
        {
            "label": "c++_offer",
            "type": "process",
            "command": "clang++",
            "args": [
                "${file}",
                "-g",
                "-o",
                "${workspaceFolder}/学习笔记/c++/代码片段/build/exe_${fileBasenameNoExtension}",
                "-Wall",
                "-std=c++17",
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "options": {
                "cwd": "${fileDirname}"
            },
        }
    ],
    "version": "2.0.0"
}
```
**参数说明**
```
label： 任务的显示名称，可以在 VSCode 中识别和执行任务时使用。
type： 任务的类型，指定了任务的执行方式。常见类型包括 "shell"（通过 shell 执行命令）、"process"（直接启动进程）、"vslaunch"（使用 Visual Studio Launch 工具）等。
command： 要执行的命令。对于 "shell" 类型的任务，这通常是命令的路径。
args： 命令的参数。指定传递给命令的参数列表。
options： 额外的选项配置，用于指定任务的执行细节。具体的选项可以因任务类型而异。
group： 将任务分组，通常用于指定默认构建任务。包含 kind（"build"）和 isDefault（是否默认任务）。
```

**其他**
**tasks.json** 可是单独使用，执行ctrl+B 就可以执行预设到tasks.json中的任务，可以执行脚本命令，也可以是启动可执行程序