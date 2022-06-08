# vscode调试c++配置

本文档介绍如何在linux+vscode环境中配置使用debug功能（ctrl+shift+D）调试程序

## 需要安装的环境或插件

### vscode
c/c++
Code Runner（可选）

### linux
gcc/g++  : sudo apt-get install gcc/g++/build-essential
gdb  : sudo apt-get install gdb

## 搭建步骤
### 创建工程
当前以formwork为例，需要含有待调试的文件。

### 建立配置文件

接下来在该目录下建立文件夹.vscode，并在文件中新建文件launch.json和task.json

* launch.json
将下面的信息写入到文件中
```
{
    // 使用 IntelliSense 了解相关属性。 
    // 悬停以查看现有属性的描述。
    // 欲了解更多信息，请访问: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "preLaunchTask": "build", //调试会话开始前执行的任务，一般为编译程序。与tasks.json的label相对应
            "name": "(gdb) Debug",       //配置文件的名字，可以随便起
            "type": "cppdbg",           //调试的类型，Vscode现在支持很多，我这里主要是C，所以只能是cppdbg
            "request": "launch",        //配置文件的请求类型，有launch和attach两种，具体看官方文档
            "targetArchitecture": "x64", //硬件内核架构，为64bit，如图设置
            "program": "${workspaceFolder}/${fileBasenameNoExtension}",   //可执行文件的路径和文件名称
            "args": [],                 //主函数调用时传入的参数
            "stopAtEntry": false,       //设为true时程序将暂停在程序入口处
            "cwd": "${workspaceFolder}",    //调试时的工作目录
            "environment": [],          //不知道干嘛的
            "internalConsoleOptions": "openOnSessionStart",
            "externalConsole": false,   //调试时是否显示控制台窗口
            "MIMode": "gdb",            //指定连接的调试器，可以省略不写
            "setupCommands": [
                {
                    "description": "为 gdb 启用整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
```
* task.json
如果调试C++，将下面command配置成g++。
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
