# vscode launch.json相关介绍

## 简介
launch.json文件用于在 Visual Studio Code 中配置调试器.可以配置调试器进行文件启动时的调试(launch模式),调试正在运行的文件(attach模式),还可以进行core文件的调试
例如, 使用lldb 以launch的形式调试可执行文件exe_
```
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug c++ templates",
            "type": "lldb",
            "request": "launch",
            "program": "${workspaceFolder}/build/exe_${fileBasenameNoExtension}",
            "args": [],
            "cwd": "${workspaceFolder}",
            "preLaunchTask": "c++_template", // 前置任务，可以是你的编译任务的名称
        }
    ]
}
```

## 文件说明
### 文件生成
- 默认组合键是`ctrl shift d`可以激活扩展,如果没有文件的话可以创建文件
- 可以使用`ctrl p`输入`debug `**注意要有空格**,可以创建文件
- 可以手动在工程下的.vscode文件夹下创建launch.json
### 文件使用
- 默认组合键是`ctrl shift d`可以激活扩展
- 可以使用`ctrl p`输入`debug `**注意要有空格**,可以选择已经编辑好的任务
### 文件结构
文件结构如下:
```
{
    "version": "0.2.0",
    "configurations": [
        {  // configuration1 },
        {  // configuration2 },
        ...
    ]
}
```
### 内容说明
**常用的配置标签说明如下**
- name: 配置名称,唯一
- type: 调试器类型一般为`cppdbg`或`lldb`
- request: 调试模式,程序调试一般为`launch`(启动模式)或`attach`(附加模式),core文件调试为`custom`
- program: 被调试的文件路径,program与pid有一个就可以
- args: 参数,一般是用于launch模式下,如果program启动需要参数的话,填写到这里
- env: 环境变量,一般是用于launch模式下,如果program启动需要配置环境变量的话,填写到这里
- cwd: 设置调试器启动的应用程序的工作目录,一般是用于launch模式下
- pid: 可以选择pid, program与pid有一个就可以

如果想使用其他的参数,可以使用触发器建议 `ctrl space`提出建议,如果不好使,可以参考[解决方法](https://blog.csdn.net/qq_43220213/article/details/129645181)后重启vscode.
也可以参考[launch.json官方资料](https://code.visualstudio.com/docs/cpp/launch-json-reference)


## 应用
### attach模式调试
```
{
    "version": "0.2.0",
    "configurations": [
        // 使用lldb attach模式 调试program
        {
            "name": "be clang++",
            "type": "lldb",
            "request": "attach",
            "program": "${workspaceFolder}/program",
        },
        // 使用lldb attach模式 可以选择pid
        {
            "name": "pid clange++",
            "type": "lldb",
            "request": "attach",
            "pid": "${command:pickProcess}",
        },
    ]
}
```
### launch模式调试
使用lldb launch模式 调试未启动的program
```
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "ut launch clang++",
            "type": "lldb",
            "request": "launch",
            // 需要指定program的路径
            "program": "${workspaceFolder}/be/ut_build_ASAN/test/doris_be_test",
            // 若启动需要参数，在此配置
            "args":[
            "--gtest_output=xml:${workspaceFolder}/be/ut_build_ASAN/gtest_output/doris_be_test.xml",
            "--gtest_print_time=true",
            "--gtest_filter=CirroFile*"],
            // 若启动需要环境变量，在此配置
            "env": {"DORIS_HOME":"${workspaceFolder}",},
            // 如果需要搭配tasks.json使用，在此配置label
            "preLaunchTask": "build be ut",
        },
    ]
}
```

### core文件调试
使用以下的配置可以使用lldb调试core文件
```
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Open a core dump",
            "type": "lldb",
            "request": "custom",
            "initCommands": [
                "target create -c ${input:coreFileName} ${workspaceFolder}/output/be/lib/doris_be"
            ]
        },
    ],
    "inputs": [
        {
            "id": "coreFileName",
            "type": "promptString",
            "description": "Enter core file path"
        }
    ]
}
```