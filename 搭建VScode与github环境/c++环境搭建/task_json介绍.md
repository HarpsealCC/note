# vscode task.json相关介绍

## 简介
在日常工作中存在大量工具用于自动化诸如代码检查、构建、打包、测试或部署软件系统等任务。包括 TypeScript 编译器，诸如 ESLint 和 TSLint 的代码检查工具，以及诸如 Make、Ant、Gulp、Jake、Rake 和 MSBuild 等构建系统。
这些工具大多从命令行运行，并自动执行软件开发循环内外的工作（编辑、编译、测试和调试）。鉴于它们在开发生命周期中的重要性，能够从 VS Code 中运行这些工具并分析其结果是很有帮助的。
在 VS Code 中，**任务可以配置为运行脚本和启动进程**，这样就可以从 VS Code 中使用许多现有工具，而无需进入命令行或编写新代码。针对工作区或文件夹的特定任务可以从工作区的 .vscode 文件夹中的 tasks.json 文件中进行配置

例如, 需要执行doris编译脚本,且不想编译be相关的java扩展,需要执行以下指令
```
export DISABLE_BE_JAVA_EXTENSIONS=ON
sh BUILD_TYPE=DEBUG build.sh --be -j80
```
可以将其写入到tasks.json中
```
{
    "version": "2.0.0",
    "tasks": [
        {  // debug模式编译be，且不编译相关的java扩展
            "label": "Build BE",
            "type": "shell",
            "command": "sh",
            "args": [
                "-c",
                "DISABLE_BE_JAVA_EXTENSIONS=ON BUILD_TYPE=Debug sh build.sh --be -j80"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
    ]
}
```
> 注意：任务支持仅在工作区文件夹上工作时可用。在编辑单个文件时不可用。
## 文件说明
### 文件生成
- 默认组合键是`ctrl shift b`可以激活扩展,如果没有文件的话可以创建文件
- 可以使用`ctrl shift p`输入`tasks`,选择配置任务,可以创建文件
- 可以手动在工程下的.vscode文件夹下创建tasks.json
### 文件使用
- 默认组合键是`ctrl shift b`可以激活扩展,可以选择已经编辑好的任务
- 可以使用`ctrl shift p`输入`tasks`,选择配置任务
### 文件结构
结构如下
```
{
    "version": "2.0.0",
    "tasks": [
        {  // task1 },
        {  // task2 },
        ...
    ]
}
```
### 内容说明
**常用的任务标签说明如下**
- label:用户界面中使用的任务标签。
- type:任务的类型。对于自定义任务，这可以是shell或process。如果shell指定，则该命令将解释为 shell 命令（例如：bash、cmd 或 PowerShell）。如果process指定，则该命令被解释为要执行的进程。
- command:实际执行的命令。
- group:定义任务属于哪个组。属于测试组的任务可以通过从ctrl shift p 指定group类型来选择任务组
- args:调用命令时输入的参数,可以分别输入,也可以使用"-c"统一输入成一行
- clear:是否在任务结束后关闭终端
- presentation:控制终端的行为
  - close: 任务结束之后是否关闭终端

如果想使用其他的参数,可以使用触发器建议 `ctrl space`提出建议,如果不好使,可以参考[解决方法](https://blog.csdn.net/qq_43220213/article/details/129645181)后重启vscode.
也可以参考[task.json schma官方资料](https://code.visualstudio.com/docs/editor/tasks-appendix)

## 应用
### 执行编译
可以单独执行,也可配合launch.json使用
```
// 举例,使用clang编译当前文件,输出到build文件夹下且可执行文件前缀为exe_
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "c++_template",
            "type": "process",
            "command": "clang++",
            "args": [
                "${file}",
                "-g",
                "-o",
                "${workspaceFolder}/build/exe_${fileBasenameNoExtension}",
                "-Wall",
                "-std=c++17",
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
        },
    ]
}
```
### 执行脚本
```
// 举例,执行clean.sh脚本清理可执行文件
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "c++_template_cleaner",
            "type": "shell",
            "command": "/bin/bash",
            "args": ["-c", "${workspaceFolder}/build/clean.sh"],
            "group": {
                "kind": "build",
                "isDefault": true
            },
        }
    ]
}
```

### 复合任务
```
{
// 举例,重启be的任务由两个顺序执行的任务组成
    "version": "2.0.0",
    "tasks": [
        {
            "label": "BE Stop Daemon"
            // ...
        },
        {
            "label": "BE Start Daemon",
            // ...
        },
        {
            "label": "Be Restart",
            "dependsOrder": "sequence",
            "dependsOn": [
                "BE Stop Daemon",
                "BE Start Daemon"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
    ]
}
```

### 变量替换

创作任务配置时，拥有一组预定义的通用变量非常有用，例如活动文件 `${file}` 或工作区根文件夹`${workspaceFolder}`。 VS Code 支持文件中字符串内的变量替换，您可以在[变量参考](https://code.visualstudio.com/docs/editor/variables-reference)中查看预定义变量的完整列表。

> 注意：并非所有属性都接受变量替换。具体来说，仅command、args、 和options支持变量替换。

同样，您可以通过在名称前添加`${config:` 来引用项目的配置设置。例如，`${config:python.formatting.autopep8Path}`返回 Python 扩展设置`formatting.autopep8Path`。

下面是自定义任务配置的示例，它使用设置定义的 autopep8 可执行文件在当前文件上执行 autopep8 python.formatting.autopep8Path：
```
{
  "label": "autopep8 current file",
  "type": "process",
  "command": "${config:python.formatting.autopep8Path}",
  "args": ["--in-place", "${file}"]
}
```

如果简单的变量替换还不够，您还可以通过inputs向文件添加一个部分来获取任务用户的输入tasks.json。
```
{
    // 对input的core文件进行调试
    "tasks": [
        {
            "type": "lldb",
            "request": "custom",
            "name": "Open a core dump",
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

## 参考资料
[Integrate with External Tools via Tasks](https://code.visualstudio.com/docs/editor/tasks)
