# **gdb相关指令**
本文大致介绍gdb常用的一些指令

跳转到指定线程
```
t <threadid>
```

打印core文件所有线程堆栈信息
```
gdb -q --batch --ex "set height 0" --ex "set logging file thread_info.txt" --ex "set logging on" --ex "thread apply all  bt" --ex "set logging off" bin/xcloudd core.xxxx
```

打印智能指针(参考具体情况)
```
p (*point).px
```

打印stl，参考《gdb打印stl》

