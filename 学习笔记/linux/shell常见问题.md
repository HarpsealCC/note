# 本文件描述一些shell中常见的问题

### 在linux下的使用复制命令cp，不让出现“overwrite”（文件覆盖）提示的方法
一般情况下使用 -f就可以
```
cp -f source_file dec_file
```
如果加了-f 还不好使
就需要查看~/.bashrc中有没有alias cp='cp -i'，如果有的话就**注释这行**，再**重启shell**