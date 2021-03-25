# **vscode与github环境连接的搭建**

## 背景介绍
本人使用的是window下安装的vscode与WSL子系统搭配的方式来使用，所以与平常的linux或者window或者mac的使用都不太一样，特别是一些插件在linux下安装与在WSL子系统安装可能会有不同，所以应该不是很顺利，持续更新遇到的坑与时而高端但是大部分都猥琐的解决方案~~

## vscode与WSL的安装

### vscode的安装
在win10上安装vscode并安装一些插件，可以看之前的<<vscode下载与安装>>

### WSL的安装
安装好vscode之后，需要在win10上安装WSL，在window下使用WSL（Windows Subsystem for Linux）试是一个linux开发者的非常省事儿的环境配置的一个方式，不用虚拟机，不用双系统随用随开，能够与window上的文件系统互通（虽然window系统上的文件一并是root权限）。但是不耽误用，在安装环境的时候注意下一就可以了。

WSL在微软的商城就能在线安装（不用登陆微软账户就可以安装），离线安装的方式暂时不弄，以后有需要再补充


## vscode连接WSL

安装了WSL使用插件Remote-WSL可以自动连接到WSL中，应该不需要其他操作（在vscode的远程资源管理时应该有提示是否连接到WSL）。连接到WSL之后的操作就可以完全按照linux下的操作来了，hhh

## git与github
在搭建vscode使用github前需要先明确git与github的概念

### 什么是git（个人理解）
git是一个代码管理工具，可以本地搭建自己使用，完全可以自己在linux环境上搭建一个git仓库管理自己的代码或者一些文档
### 什么是github（个人理解）
github是一个网站，你可以把本地的git的内容同步到网络上，此外还可以使用github来查看其他开源优质的工程代码
### git与github（个人理解）
如果你只是想管理自己的代码或文档，给他们添加一个版本控制功能，那可以直接使用本地的git（linux是自带的，window需要安装git），如果你想让自己的代码可以在不同的地方随时查看与修改（有网），比如我如果在公司写了个文档，但是没有写完，回家想继续编辑，我原来的方法就是优盘或者微信什么的备份一下，之后再在家里电脑上继续修改，不是很方便。如果使用git+github，在公司写了之后上传到github上，之后回家只要从远端拉下来就可以继续的写文档了。

## 搭建远端仓库并与本地仓库做关联

**以下的本地操作均在WSL的终端上或者vscode连接到WSL上之后的终端操作**
### 搭建远端仓库
首先你需要在github上有个账号，之后再在网页上建立一个仓库
可以参考[百度经验]，或者在网上搜索一下
<https://jingyan.baidu.com/article/c843ea0ba1110d77921e4a7e.html>

### 远端仓库与本地仓库做关联

* 检查git是否安装
```
git --version
```
如果没有安装就 
```
sudo apt-get install git
```
* 确定git安装后，需要在远端github上添加ssh秘钥，这里认为本地git还没有与远端github建立过连接，首先要配置git的用户名和邮箱，在本地配置的git用户名与邮箱可以随意起名，格式正确就行
```
git config --global user.name 'username'
git config --global user.email 'youEmail'
e.g.
git config --global user.name 'lcz'  // 没有提示就是成功
git config --global user.email 'lcz@git.com'  // 没有提示就是成功
```
之后，再执行
```
ssh-keygen -t rsa -C "youEmail"
e.g.
ssh-keygen -t rsa -C "lcz@git.com"
```
如果遇到提示就一路回车，之后会在用户目录下生成.ssh的隐藏文件夹
```
pachina@DESKTOP-R581VPJ:~$ ll .ssh
total 8
drwx------ 1 pachina pachina 4096 Mar 24 16:18 ./
drwxr-xr-x 1 pachina pachina 4096 Mar 25 14:14 ../
-rw------- 1 pachina pachina 2610 Mar 24 16:16 id_rsa
-rw------- 1 pachina pachina  578 Mar 24 16:16 id_rsa.pub
-rw-r--r-- 1 pachina pachina 1768 Mar 24 16:20 known_hosts
```
将id_rsa.pub中的一大堆内容复制之后，贴到github上的ssh秘钥区域就可以了

* 在远端添加了秘钥之后就可以开始关联远程库了
```
先删除以防其他链接占用
git remote rm origin
之后执行
git remote add origin git@github.com/username/nihao.git
上面的url地址是在github上建立远端仓库时的ssh地址，一般在下载代码时候就能看到
之后执行
git remote -v
如果有打印的话就是已经建立连接了，之后就可以使用vscode对文本进行提交
```


**需要注意：**

用WSL建立连接时，本地仓库要建立到WSL用户的根目录下，不能建立在window的文件系统下，否则建立连接之后提交会报权限不正确之类的问题。
