# doris工程中使用到的.vscode相关的配置

## launch.json
```
{
    "version": "0.2.0",
    "configurations": [
        {  // 使用lldb attach模式 调试be
            "name": "be clang++",
            "type": "lldb",
            "request": "attach",
            "program": "${workspaceFolder}/output/be/lib/doris_be",
        },
        {  // 使用lldb attach模式 调试be ut,需要保证ut正在运行,一般是添加sleep
            "name": "ut clang++",
            "type": "lldb",
            "request": "attach",
            "program": "${workspaceFolder}/be/ut_build_ASAN/test/doris_be_test",
        },
        {  // 使用lldb launch模式 调试be ut,此方法不用添加sleep,指定gtest_filter参数
            "name": "ut launch clang++",
            "type": "lldb",
            "request": "launch",
            "program": "${workspaceFolder}/be/ut_build_ASAN/test/doris_be_test",
            "args":[
            "--gtest_output=xml:${workspaceFolder}/be/ut_build_ASAN/gtest_output/doris_be_test.xml",
            "--gtest_print_time=true",
            "--gtest_filter=CirroFile*"],
            "env": {"DORIS_HOME":"${workspaceFolder}",},
            "preLaunchTask": "build be ut",
        },
        {  // 使用lldb launch模式 可以选择pid
            "name": "pid clange++",
            "type": "lldb",
            "request": "attach",
            "pid": "${command:pickProcess}",
        },
    ]
}
```

## tasks.json
```
{
    "version": "2.0.0",
    "tasks": [
        {  // 以debug模式编译整个工程
            "label": "Build Project",
            "type": "shell",
            "command": "sh",
            "args": [
                "-c",
                "BUILD_TYPE=Debug sh build.sh --fe --be -j80"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
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
        {  // clean后 debug模式编译工程
            "label": "Rebuild Project",
            "type": "shell",
            "command": "sh",
            "args": [
                "-c",
                "BUILD_TYPE=Debug sh build.sh --fe --be --clean -j80"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
        {  // 启动fe
            "label": "Start FE Daemon",
            "type": "shell",
            "command": "sh",
            "args": ["-c",
            "${workspaceFolder}/output/fe/bin/start_fe.sh --daemon && sleep 3"],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
        {  // 启动be
            "label": "Start BE Daemon",
            "type": "shell",
            "command": "sh",
            "args": ["-c",
            "${workspaceFolder}/output/be/bin/start_be.sh --daemon && sleep 3"],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
        {  // 停止fe
            "label": "Stop FE Daemon",
            "type": "shell",
            "command": "${workspaceFolder}/output/fe/bin/stop_fe.sh",
            "args": [],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
        {  // 停止be
            "label": "Stop BE Daemon",
            "type": "shell",
            "command": "${workspaceFolder}/output/be/bin/stop_be.sh",
            "args": [],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
        {  // 提交当前commit
            "label": "Push to Origin",
            "type": "shell",
            "command": "git",
            "args": [
                "push",
                "-u",
                "origin",
                "${gitBranch}",
                "--push-option=--no-ticket-check"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
        {  // 编译 执行 生成coverage，带有filter
            "label": "Run be ut",
            "type": "shell",
            "command": "sh",
            "args": [
            "${workspaceFolder}/run-be-ut.sh",
            "--run",
            "--coverage",
            // "--filter=CirroFileFixLengthPlainDecoder*",
            "--filter=CirroFile*",
            "-j80"],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
        {  // clean后 编译 执行 生成coverage，带有filter
            "label": "Run be ut clean",
            "type": "shell",
            "command": "sh",
            "args": [
            "${workspaceFolder}/run-be-ut.sh",
            "--run",
            "--coverage",
            "--filter=CirroFile*",
            "--clean",
            "-j80"],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
        {  // 生成coverage后，启动http服务，用于访问  端口号8524
            "label": "Show be coverage html",
            "type": "shell",
            "command": "sh",
            "args": [ "-c",
            "cd ${workspaceFolder}/be/ut_build_ASAN/test/report/ && python -m SimpleHTTPServer 8524 && tail -f /dev/null"],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
        {  // 执行clang format检查
            "label": "Run Check Clang format",
            "type": "shell",
            "command": "sh",
            "args": ["-c",
            "${workspaceFolder}/build-support/check-format.sh"],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
        {  // 仅编译be ut
            "label": "build be ut",
            "type": "shell",
            "command": "sh",
            "args": [
            "${workspaceFolder}/run-be-ut.sh",
            "-j80"],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
    ]
}
```

## setting.json
```
{
    // "lldb.consoleMode": "evaluate", //调试控制台模式为终端命令模式，可调用lldb命令
    "lldb.launch.sourceLanguages": [ //调试语言
        "cpp",
        "c"
    ],
    "lldb.launch.expressions": "native", //使用原生表达式
    "lldb.displayFormat": "auto",
    "lldb.dereferencePointers": false,
    "lldb.showDisassembly": "auto",
    // 找不到编译数据库(compile_flags.json 文件)时使用的编译器选项,这样的缺陷是不能直接索引同一项目的不同文件,只能分析系统头文件、当前文件和被include的文件
    "clangd.fallbackFlags": [
        "-std=c++20",
        // 增加项目自身头文件依赖路劲，因为使用vs2019编译不会生成compile_command.json文件，项目自己的头文件就不会找到
        "-I/root/lcz_cirrodata_olap/be", // 项目根目录
        "-I/root/lcz_cirrodata_olap/thirdparty/installed/include", // 第三方依赖的头文件目录
        "-I/var/local/thirdparty/installed/include",
        "-I/var/local/ldb-toolchain/include"
    ],
    // Clangd 运行参数(终端输入 clangd --help-list-hidden 可查看更多)
    "clangd.arguments": [
        "--all-scopes-completion", // 全局补全(补全建议会给出在当前作用域不可见的索引,插入后自动补充作用域标识符),例如在main()中直接写cout,即使没有`#include <iostream>`,也会给出`std::cout`的建议,配合"--header-insertion=iwyu",还可自动插入缺失的头文件
        "--background-index", // 后台分析并保存索引文件
        "--clang-tidy", // 启用 Clang-Tidy 以提供「静态检查」
        //"--compile-commands-dir=/home/lcz/lcz/git/gitlab/lcz_cirrodata_olap/be/build_DEBUG", // 编译数据库(compile_commands.json 文件)的目录位置
        "--compile-commands-dir=/root/lcz_cirrodata_olap/be/build_DEBUG",
        "--completion-parse=auto", // 当 clangd 准备就绪时，用它来分析建议
        "--completion-style=detailed", // 建议风格：打包(重载函数只会给出一个建议);还可以设置为 detailed
        // "--query-driver=/usr/bin/clang++", // MAC 上需要设定 clang 编译器的路径，也可以是 /usr/local/opt/llvm/bin/clang++
        // 启用配置文件(YAML格式)项目配置文件是在项目文件夹里的“.clangd”,用户配置文件是“clangd/config.yaml”,该文件来自:Windows: %USERPROFILE%\AppData\Local || MacOS: ~/Library/Preferences/ || Others: $XDG_CONFIG_HOME, usually ~/.config
        "--enable-config",
        "--fallback-style=Webkit", // 默认格式化风格: 在没找到 .clang-format 文件时采用,可用的有 LLVM, Google, Chromium, Mozilla, Webkit, Microsoft, GNU
        "--function-arg-placeholders=true", // 补全函数时，将会给参数提供占位符，键入后按 Tab 可以切换到下一占位符，乃至函数末
        "--header-insertion-decorators", // 输入建议中，已包含头文件的项与还未包含头文件的项会以圆点加以区分
        "--header-insertion=iwyu", // 插入建议时自动引入头文件 iwyu
        "--log=verbose", // 让 Clangd 生成更详细的日志
        "--pch-storage=memory", // pch 优化的位置(Memory 或 Disk,前者会增加内存开销，但会提升性能)
        "--pretty", // 输出的 JSON 文件更美观
        "--ranking-model=decision_forest", // 建议的排序方案：hueristics (启发式), decision_forest (决策树)
        "-j=32", // 同时开启的任务数量
        "--query-driver=/var/local/ldb-toolchain/bin/clang++"
    ],
    "git.ignoreLimitWarning": true,
}
```