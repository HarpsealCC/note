# **Git Submodule**

## Submodule简介
当git中的项目中需要依赖其他子模块时，有一种使用Submodule来控制的方案

## 使用
见
https://zhuanlan.zhihu.com/p/87053283




## 其他
### 修改submodule的clone路径
在一些情况下，submodule的clone方式是用http路径的这样在网络不好的情况下会导致clone工程失败，用ssh的方案能够比较好的的规避这个问题。

**方法**

首先进入到项目目录中
```
vi .gitmodules

#修改url为git@...
[submodule "deps/googletest"]
        path = deps/googletest
        url = git@github.com/google/googletest.git
[submodule "deps/googlemock"]
        path = deps/googlemock
        url = git@github.com/google/googlemock.git

```
