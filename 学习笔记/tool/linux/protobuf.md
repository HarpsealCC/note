<!--
 * @Author: your name
 * @Date: 2021-11-29 18:08:49
 * @LastEditTime: 2021-12-03 16:18:10
 * @LastEditors: Please set LastEditors
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

## **使用protobuf生成代码**
生成c++代码指令
```
protoc --cpp_out=./ test.proto   // 生成test.pb.cc 与 test.pb.h（以这两个代码文件为例）
```
生成java代码指令
```
protoc --java_out=./ test.proto   // 根据java_outer_classname生成对应的.java (下面使用protobuf.java为例)
```
生成python代码指令  // 暂未进行实际操作
```
protoc --python_out=./ test.proto
```

## **对生成的protobuf的代码进行编译**
### **C++**
代码中include test.pb.h，在编译时包含相应的头文件路径与lib库路径即可
```
e.g.
g++ -o test demo.cpp -I{PROTOCINPATH} \   // protobuf include路径
-L{PROTOCLIBPATH} \  // protobuf libpath
-lpthread -lprotobuf -std=c++11  // 这三项必须加，不然有奇怪的报错
```

```
c++编译时遇到的问题：
https://blog.csdn.net/weixin_39639686/article/details/110641630?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_title~default-0.essearch_pc_relevant&spm=1001.2101.3001.4242.1
```


### **JAVA**
首先，使用maven工程，将protobuf.java文件进行编译打成jar包，pom.xml中需要配置如下依赖，version需要在3.0以上，网上2.5.0版本会有报错
```
<dependencies>
<dependency>
    <groupId>com.google.protobuf</groupId>
    <artifactId>protobuf-java</artifactId>
    <version>3.9.0</version>
</dependency>
</dependencies>
```
使用idea打包就可以。
然后，将这个依赖jar包与idea生成的jar包添加到要使用的java目录下，编译
```
e.g.
javac -cp ./protobuf-java-3.9.0.jar:./Protobuftest-0.1.jar Demo.java
```
运行
```
e.g.
java -cp ./protobuf-java-3.9.0.jar:./Protobuftest-0.1.jar: Demo   // 运行时候需要添加所有依赖的jar包路径且最后一个分号不能少，Demo对应Demo.class文件
```

### **Python**

暂未使用