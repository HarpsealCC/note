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

接下来在该目录下建立文件夹.vscode，并在文件中新建文件c_cpp_properties.json和launch.json

* c_cpp_properties.json
好像不用写这个文件也可以调试。。。。
```
ctrl+shift+p
输入
edit
选择c++ edit Configurations(json)
建立c_cpp_properties.json

在"includePath"中，
输入头文件的路径
```

* launch.json
在调用debug功能时如果没有会自动生成一个初始文件，将下面的信息写入到文件中

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
* task.json（目前不需要配置）
此文件可能是需要直接编译cpp文件，如果有编译成功的可执行文件用来调试，可以不用配置这个文件，如果调试C++，将下面command配置成g++。
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
