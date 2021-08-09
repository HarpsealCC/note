<!--
 * @Author: your name
 * @Date: 2021-08-09 11:37:38
 * @LastEditTime: 2021-08-09 11:42:23
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /学习笔记/gdb/gdb打印stl.md
-->
# **gdb打印stl的方法**

```
gdb常用打印"p variable-name"，这种方式查看STL容器类，只会显示该容器的部分信息，比如p map，如果map中有1000个键值对，那么该次打印并不能打印全部。这时就需要stl-views.gdb这个脚本。将上述下载stl-veiws.gdb文件，放到~/目录下，将其改名为~/.gdbinit，或者在已有的.gdbinit文件中用source ~/.stl-views.gdb命令将其包含（亦可在进入gdb后source ~/.stl-views.gdb）。这样你就可以用如下命令显示STL容器类了。
```

| Data type | GDB command |
|  ----  | ----  |
|std::vector<T>|    pvector stl_variable|
|std::list<T>|  plist stl_variable T|
|std::map<T,T>|	pmap stl_variable|
|std::multimap<T,T>|	pmap stl_variable|
|std::set<T>|	pset stl_variable T|
|std::multiset<T>|	pset stl_variable|
|std::deque<T>|	pdequeue stl_variable|
|std::stack<T>|	pstack stl_variable|
|std::queue<T>|	pqueue stl_variable|
|std::priority_queue<T>|	ppqueue stl_variable|
|std::bitset<n>|	pbitset stl_variable|
|std::string|	pstring stl_variable|
|std::widestring|	pwstring stl_variable|
