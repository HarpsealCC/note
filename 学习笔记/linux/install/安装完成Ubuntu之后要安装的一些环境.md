<!--
 * @Author: your name
 * @Date: 2021-12-06 11:35:56
 * @LastEditTime: 2021-12-06 11:37:07
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /note/学习笔记/linux/install/安装完成Ubuntu之后要安装的一些环境.md
-->

# linux环境配置（持续更新）

本文主要介绍刚刚安装完成linux（Ubuntu）系统或者子系统之后需要安装哪些环境

## 软件安装

### 更换源
见[更换源](../config/更换源.md)

### 安装ssh
```
sudo apt install -y openssh-server
```
### 安装net-tools
```
sudo apt install net-tools
```

### 安装git
```
sudo apt-get install git
```

### 配置github520
安装
```
sudo apt install nscd
```
访问[GitHub520](https://github.com/521xueweihan/GitHub520),将内容粘贴到`/etc/hosts`中
重启
```
sudo /etc/init.d/nscd restart
```

## c++相关的环境与配置

### c/c++编译器
#### gcc && g++
```
sudo apt-get install build-essential   // gcc/g++编译器
```

#### clang && clang++
llvm中包含clang && clang++可以直接安装llvm，有两种方法
- 方法1：直接安装默认版本，不过ubuntu默认安装版本为14
```
sudo apt update && sudo apt upgrade
sudo apt install clang
```
- 方法2：可以选择安装指定版本，此方法只在debian与ubuntu系统可用
```
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh 18  // sudo ./llvm.sh <版本号>

sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-18 100  // 设为默认编译器
sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-18 100  // 设为默认编译器

clang --version
```
### cmake
```
sudo apt install cmake  // cmake
```
<a name="java安装"></a>

## java相关的环境与配置
### java安装
（一些概念：
jre：java程序运行时候的依赖环境
jdk：除了jre外，还有一些额外的开发编译功能）
```
sudo apt install openjdk-11-jdk  // 安装java
sudo apt install openjdk-19-jre-headless  // 也可以安装版本高一点
```
### 更新maven的setting.xml
使用[setting.xml](./settings.txt)内容，替换`.m2/setting.xml`中的内容


### 代码管理
```
sudo apt install subversion  // 安装svn
// git一般自带
```
### 性能相关
```
sudo apt install sysstat   // 安装监测系统性能及效率的一组工具
```

### 网络相关
```
sudo apt install inetutils-traceroute  // 查询路由
```

### 调试相关
```
sudo apt install gdb  // 安装gdb调试工具
```
pstack为依托于gdb的一个脚本，安装了gdb后，ubuntu环境可能没有这个脚本，需要
```
vi /usr/bin/pstack
```
将下面的脚本内容复制到/usr/bin/pstack中，并赋予权限 **目前pstack在ubuntu中只能使用sudo pstack使用**
```
#!/bin/sh

if test $# -ne 1; then
    echo "Usage: `basename $0 .sh` <process-id>" 1>&2
    exit 1
fi

if test !  -r /proc/$1; then
    echo "Process $1 not found." 1>&2
    exit 1
fi

# GDB doesn't allow "thread apply all bt" when the process isn't
# threaded; need to peek at the process to determine if that or the
# simpler "bt" should be used.

backtrace="bt"
if test -d /proc/$1/task ; then
    # Newer kernel; has a task/ directory.
    if test `/bin/ls /proc/$1/task | /usr/bin/wc -l` -gt 1 2>/dev/null ; then
        backtrace="thread apply all bt"
    fi
elif test -f /proc/$1/maps ; then
    # Older kernel; go by it loading libpthread.
    if /bin/grep -e libpthread /proc/$1/maps > /dev/null 2>&1 ; then
        backtrace="thread apply all bt"
    fi
fi

GDB=${GDB:-/usr/bin/gdb}

# Run GDB, strip out unwanted noise.
# --readnever is no longer used since .gdb_index is now in use.
$GDB --quiet -nx $GDBARGS /proc/$1/exe $1 <<EOF 2>&1 |
set width 0
set height 0
set pagination no
$backtrace
EOF
/bin/sed -n \
    -e 's/^\((gdb) \)*//' \
    -e '/^#/p' \
    -e '/^Thread/p'
```
