
# vscode 下载与安装

## vscode 下载

国内访问外网可能下载比较慢，可以参考下面的网址中的解决方法：

```
https://zhuanlan.zhihu.com/p/112215618
```

首先在官网找到需要下载的文件，点击下载。

在浏览器或者下载软件中就可以看到这么一个下载地址了，将其复制下来（如下图箭头所指）。

然后将红框内的部分更换为如下内容：

vscode.cdn.azure.cn <--------就是左边这个

更新后的地址为：http://vscode.cdn.azure.cn/stable/78a4c91400152c0f27ba4d363eb56d2835f9903a/VSCodeUserSetup-x64-1.43.0.exe

这个就是国内的镜像了点开后你会发现速度直接起飞。

## vscode 安装

### 软件安装

直接打开安装包安装就可以

### 插件列表

    1、Chinese (Simplified) Language Pack for Visual Studio Code
    2、c/c++
    3、plantuml ：绘制uml图（remote）
    4、Markdown ：markdown相关组件（remote）
    5、Markdown Plantuml Preview ：markdown中显示plantuml（remote）
    6、vscode-pandoc ： 将makedown文件转换成pdf等文件（remote暂时不好使）
    7、Markdown pdf ： markdown转pdf（remote）
    8、Remote-SSH ： 登陆ssh（local）
    9、Remote-WSL ：登陆wsl（local）
    10、Bracket Pair Colorizer 2 ：括号标记（local）
    11、GitLens — Git supercharged ：有许多git功能的扩展，如显示提交日期等（remote）
    12、tabout ：快速跳出括号引号等（remote）
    13、翻译或者comment translate(wsl子系统上使用会有问题) ：（remote）
    14、c++ intellisense ：c++的辅助工具（remote）
    15、TODO Tree ：显示被标记为todo的待办事件（remote）
    16、Bookmarks  ：书签功能（remote）
    17、koroFileHeader  ：自动生成头文件（remote）
    18、Switcher  ：切换同名文件，如.h与.cpp之间，可以互相切换（remote）
    19、Git Graph  : 图形显示git提交记录（remote）
    20、Markdown Image：方便地在 Markdown 中插入图片，支持本地、图床或对象存储（remote暂时不好使）

### 使用环境

vscode 可以在 window、mac 或者 linux 上运行，考虑到开发与使用的情况，我比较倾向于在 window 上安装 vscode，但是编译与运行环境和插件安装都使用 WSL 子系统来进行。
有些插件可能在 wsl 子系统上无法正常工作

也可以在网上买服务器进行搭建，这样各个软件或者插件运行起了问题会更少

也可以使用虚拟机搭建 linux 系统作为服务器进行开发（2023-11-19）

# 2024 年更新

## vscode 下载

访问[vscode官网下载地址](https://code.visualstudio.com)可以直接下载了

## vscode 安装
### 软件安装
一般在windows上进行安装，然后可以使用windows上的vscode访问wsl，远程服务器，虚拟机上的linux进行远程开发与调试。
如果远程linux服务器没有链接到外网，可以将对应版本的vscode连接到一个有网的服务器，然后将~/.vscode打包，上传到没有网的服务器就可以了。
需要注意，如果是windows环境没有联网，要检查一下windows user 下的.vscode文件夹下有没有之前残留的安装文件，可以删除，避免有低版本的插件之类。

### 插件列表

#### markdown相关
- **plantuml:** 可以绘制uml图， 搭配Markdown Plantuml Preview使用, 需要安装[jre/jdk](../学习笔记/linux/install/安装完成Ubuntu之后要安装的一些环境.md#java安装)和[plantuml.jar](./安装与配置plantuml相关环境.md)
- **Markdown:** 提供markdown相关功能
- **Markdown All in One:** 已知的可以提供自动生成目录的功能
- **Markdown Plantuml Preview:** 可以在markdown文件中显示plant uml图, 需要配置[markdown-preview-enhanced.plantumlJarPath](./安装与配置plantuml相关环境.md)
- **Markdown Preview Enhanced:** 强大的markdown插件，提供很多预览功能，可以将markdown文件导出为html/pdf文件，本身也提供了一些绘图功能，不过uml能力不如plantuml，详情可以参考[说明文档](https://shd101wyy.github.io/markdown-preview-enhanced/#/zh-cn/)
- **注意：** 不必安装markdown pdf相关的插件，可以使用**Markdown Preview Enhanced export html**然后搭配浏览器插件**singlefile**保存带有uml图片的html或者直接保存成pdf，效果更好。


#### c/c++相关
- **C/C++:** 据说是微软自研的vscode插件，提供了c/c++的跳转，语法补全，debug调试等功能，不过有时候跳转有问题，占内存也比较大，优点是不用额外有什么配置
- **clangd:** clang/clang++调试推荐的插件，拥有比c/c++更快的跳转，配合.clang-tidy与.clang-format文件有很好的静态分析能力，不过配置不太容易，且需要配合cmake生成的compile_commands.json文件来使用 **TODO(lcz) 添加clang-tidy clang-format说明文档**
- **clang-format:** 如果没有使用clangd，可以安装此插件用于格式化c/c++代码风格
- **lldb:** 搭配clangd使用，可以进行gdb调试，如果使用此插件进行调试需要在**launch.json**中修改type选项为"lldb" **TODO(lcz):补充举例**
- **Hex Editor:** 可以显示二进制数据，同时在gdb调试过程中也可以辅助显示
- **cmake&cmake tools:** 常用的cmake工具，目前可以搭配**tasks.json与launch.json**进行一些小项目(demo)的快速构建与调试**TODO(lcz): 补充举例文档**
- **Doxygen Documentation Generator:** 可以为文件，class/struct和函数快速生成注释**TODO (lcz) 单独文件描述操作**
- **Error Lens:** 在代码中提示对应的警告和错误，但是搭配clang-tidy可能可读性不是很好

#### docker相关
- **docker:** 图形化的容器管理插件，不过需要在服务器上安装好docker，并指定docker的可执行程序地址（默认在/usr/bin下就不用了）
- **Dev Containers:** 此插件可以让vscode在docker容器中进行开发

#### git相关
- **gitlens:** 目前用来提示代码的提交信息和快速切换分支，只能使用基础功能，额外功能需要收费
- **git graph:** 用来图形化显示git的分支情况

#### 其他
- **Bookmarks:** 书签
- **Material Icon Theme:** 美化文件图标
- **Path Intellisense:** 自动补全路径
- **Stats Bar:** 实时监控服务器性能
- **翻译:** 轻量级的翻译插件
- **Chinese (Simplified) (简体中文):** 中文插件
- **todo tree:** 
