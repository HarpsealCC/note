# vscode配置java开发环境
## 简介
本文介绍配置可以使用vscode 配合插件进行java程序调试的环境

## 环境信息
在此以doris fe调试举例：
- 代码版本： doris 2.3.0[^1]
- 系统：docker 2.1.0 build-env-ldb-toolchain-latest(centos7)
[^1]: 旧版本可能存在问题，在调试时有串行的现象，原因未知

## java调试环境
需要在docker中安装必要的插件
### 插件
- Language Support for Java(TM) by Red Hat
setting配置信息：
```
    "java.jdt.ls.vmargs": "-XX:+UseParallelGC -XX:GCTimeRatio=4 -XX:AdaptiveSizePolicyWeight=90 -Dsun.zip.disableMemoryMapping=true -Xmx12G -Xms12G -Xlog:disable",
    "java.compile.nullAnalysis.mode": "disabled",
```
其中-Xmx12G -Xms12G 以实际系统内存使用量为准
- Debugger for Java
使用默认参数即可

### doris启动项配置
在JAVA_OPTS最开始部分添加
```
JAVA_OPTS="-agentlib:jdwp=transport=dt_socket,server=y,suspend=n,address=15005 [...]"
```
其中address为端口信息，注意不要冲突`netstat -tuln | grep 15005`

### launch.json文件配置
在[launch.json文件](./c++环境搭建/launch_json介绍.md)中添加如下配置
```
{
    "version": "0.2.0",
    "configurations": [
        {
            "type": "java",
            "request": "attach",
            "name": "Attach (fe)",
            "processId": "${command:PickJavaProcess}"
        },
    ]
}
```