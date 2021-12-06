<!--
 * @Author: lcz
 * @Date: 2021-12-03 16:24:00
 * @LastEditTime: 2021-12-06 14:19:16
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%A
 * @FilePath: /note/学习笔记/c++/jni的使用.md
-->
# **jni的使用**

本文主要记录c++通过jni接口调用java方法的简单方式

假设工作目录为/home ，**这个涉及到java类的调用路径关系，需要先严格按照路径来执行，如果对jni和java有一定的认知之后，可以不拘泥于此设定**
## **1.java端**
1）mkdir lcz & cd lcz
2) 创建SubClass.java文件，内容如下：
```
// package lcz;  // 使用包名需要mkdir lcz并把生成的class放入

public class SubClass {
private String name = null;
public SubClass(String name){
this.name = name;
}

public void say(){
System.out.println("Hello " + this.name);
}
}
```
3) 创建Demo.java文件，内容如下：
```
// package lcz;  // 使用包名需要mkdir lcz并把生成的class放入

public class Demo {


public static void main(String[] args) {
new Demo("liuchengzhuo").myCall();
}


public Demo(){
//System.out.println("in default constructor");
this.name = "default";
//System.out.println("name is " + this.name);
}

private String name = null;
public Demo(String name){
//System.out.println("in special constructor");
this.name = name;
//System.out.println("name is " + this.name);
}

public void myCall(){
SubClass s = new SubClass(this.name);
s.say();
}
}
```
4) 编译文件
```
javac *.java
```
如果java程序中import其他package，需要设置CLASSPATH或者**javac -cp [.:jar包路径:]**
```
e.g.
javac -cp ./log4j-1.2.17.jar:./protobuf-java-3.9.0.jar:./Protobuftest-0.1.jar:  *.java
```

5) 查看方法签名
```
javap -classpath ./ -s Demo
```
## **2. C++端**
1) 创建TestJNI.h文件，内容如下：
```
#ifndef _TESTJNI_
#define _TESTJNI_

#include <jni.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class TestJNI
{
    public:
        TestJNI();
        jstring NewJString(const char *str);
        void say(string name);
    private:
        JavaVMOption options[1];
        JNIEnv *env;
        JavaVM *jvm;
        JavaVMInitArgs vm_args;
        long status;
};
#endif
```
2) 创建TestJNI.cpp文件，内容如下：

```
#include "TestJNI.h"

TestJNI::TestJNI()
{
    options[0].optionString = "-Djava.class.path=.";  // 如果java程序中包含其他jar包，需要在此填写jar包地址
    // e.g.   
    // options[0].optionString = "-Djava.class.path=.:./Protobuftest-0.1.jar:./protobuf-java-3.9.0.jar";
    vm_args.version = JNI_VERSION_1_2;
    vm_args.nOptions = 1;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = JNI_TRUE;
    status = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
}

jstring TestJNI::NewJString(const char *str)
{
    if(status == JNI_ERR || str == NULL)
        return 0;
    jclass strClass = env->FindClass("Ljava/lang/String;");
    jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = env->NewByteArray(strlen(str));
    (env)->SetByteArrayRegion(bytes, 0, strlen(str), (jbyte*)str);
    jstring encoding = env->NewStringUTF("GB2312");
    return (jstring)(env)->NewObject(strClass, ctorID, bytes, encoding);
}



void TestJNI::say(string name)
{
    if(status != JNI_ERR){
        jclass cls = env->FindClass("Demo");  // 同一级目录不是"./Demo"而是"Demo",如果是package，需要添加class路径，e.g. "lcz/Demo"
                                              // 具体名称规则参考
        jmethodID mid = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;)V");
        jstring arg = NewJString(name.c_str());
        jobject demo = env->NewObject(cls, mid, arg);
        mid = env->GetMethodID(cls, "myCall", "()V");
        env->CallObjectMethod(demo, mid);
    }
}

int main()
{
    TestJNI test;
    test.say("liuchengzhuo");
}
```
3) 编译生成可执行文件，需要JAVA_HOME（/usr/local/jdk）与JRE_HOME（/usr/local/jdk/jre）,两个-I中包括jni相关的头文件，-L中包括jvm相关的动态库(.so)
```
g++ TestJNI.cpp -o test -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L${JRE_HOME}/lib/amd64/server -ljvm
```