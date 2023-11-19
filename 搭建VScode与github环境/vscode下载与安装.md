<!--
 * @Author: your name
 * @Date: 2021-07-10 11:42:22
 * @LastEditTime: 2023-01-09 10:38:03
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /github/harpseal/搭建VScode与github环境/vscode下载与安装.md
-->
<!--
 *                        _oo0oo_
 *                       o8888888o
 *                       88" . "88
 *                       (| -_- |)
 *                       0\  =  /0
 *                     ___/`---'\___
 *                   .' \\|     |// '.
 *                  / \\|||  :  |||// \
 *                 / _||||| -:- |||||- \
 *                |   | \\\  - /// |   |
 *                | \_|  ''\---/''  |_/ |
 *                \  .-\__  '-'  ___/-. /
 *              ___'. .'  /--.--\  `. .'___
 *           ."" '<  `.___\_<|>_/___.' >' "".
 *          | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *          \  \ `_.   \_ __\ /__ _/   .-` /  /
 *      =====`-.____`.___ \_____/___.-`___.-'=====
 *                        `=---='
 *
 *
 *      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *            佛祖保佑       永不宕机     永无BUG
 *
 *        佛曰:
 *                写字楼里写字间，写字间里程序员；
 *                程序人员写程序，又拿程序换酒钱。
 *                酒醒只在网上坐，酒醉还来网下眠；
 *                酒醉酒醒日复日，网上网下年复年。
 *                但愿老死电脑间，不愿鞠躬老板前；
 *                奔驰宝马贵者趣，公交自行程序员。
 *                别人笑我忒疯癫，我笑自己命太贱；
 *                不见满街漂亮妹，哪个归得程序员？
 -->

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
