<!--
 * @Author: your name
 * @Date: 2021-11-29 18:08:49
 * @LastEditTime: 2021-11-29 18:08:50
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /note/学习笔记/tool/linux/protobuf.md
-->

# **protobuf**

```
Protocol Buffers是Google开发一种数据描述语言，能够将结构化数据序列化，可用于数据存储、通信协议等方面。
linux与windows下均有成熟的工具可以使用，本文介绍的是linux下的工具使用
```

## **protobuf的安装**

linux下安装：
以ubuntu为例：
```
protoc --version  // 查看是否安装protobuf
apt-get install protobuf-compiler
```
如果安装成功：
```
输入：
protoc --version
输出：
libprotoc 3.12.4
```

## **protobuf的使用**
生成c++代码指令
```
protoc --cpp_out=./ test.proto
```
生成java代码指令
```
protoc --java_out=./ test.proto
```
生成python代码指令
```
protoc --python_out=./ test.proto
```

```
编译时遇到的问题：
https://blog.csdn.net/weixin_39639686/article/details/110641630?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_title~default-0.essearch_pc_relevant&spm=1001.2101.3001.4242.1
```