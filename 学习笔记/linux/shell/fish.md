# 🐟 Fish（Friendly Interactive Shell）

## 简介
- 全称：Friendly Interactive Shell
- 定位：一个更现代、用户友好的交互式 shell。
- 特点：
    - 默认就有语法高亮、自动建议（auto-suggestion）、命令补全。
    - 配置更简单，不用折腾太多 .rc 文件。
    - 适合人群：追求更高效率和现代体验的日常终端用户。
    - ❗**注意：** 不完全兼容 POSIX sh 语法 → 用 fish 写的脚本可能不能直接在 bash/sh 里运行。

## 安装与启动
可以通过包管理器进行安装，以Ubuntu为例
```
sudo apt install fish
```

安装完成之后执行`fish`指令即可启动fish

配置文件：`~/.config/fish/config.fish`每次启动时都会加载这个文件

## 设为系统默认shell

1. 找到fish的安装位置
```
⋊> which fish
/usr/bin/fish
```
2. 将路径添加到`/etc/shells`中
3. 更改当前用的的默认shell为Fish，输入密码
```
chsh -s /usr/bin/fish
```

### vscode 不启用fish
Linux目前看是直接同步的

## fish_config
如果是图形化的界面，在终端执行`fish_config`指令可以在浏览器中启动一个网页版的配置界面，可以直接点选。

❗**注意：** Ubuntu自带的火狐浏览器无法打开这个网页，原因见[fish_config doesn't work on Ubuntu 22](https://github.com/fish-shell/fish-shell/issues/8844)，看评论是Ubuntu自带的火狐浏览器有问题，如果想启用此网页功能，可以把火狐卸载，安装个其他的浏览器，可以安装[vivalid](https://help.vivaldi.com/zh-hans/desktop-zh-hans/install-update-zh-hans/install-snapshots-on-non-deb-rpm-distros/)


## 插件管理器oh-my-fish
可以使用omf（oh-my-fish）对fish的插件进行管理，这个插件管理器是个[开源项目](https://github.com/oh-my-fish/oh-my-fish?tab=readme-ov-file)

### 安装
按照项目中的说明文档介绍，有多种安装方法，目前试过第一种是可以的，不过需要保证linux环境可以访问外网，可以参考[VMware虚拟机通过宿主机的v2ray进行外网访问](../proxy/VMware虚拟机通过宿主机的v2ray进行外网访问.md)进行环境配置。
执行：
```
curl https://raw.githubusercontent.com/oh-my-fish/oh-my-fish/master/bin/install | fish
```
### 使用

1. `omf list`：列出已经安装的插件与主题
2. `omf theme`：列出有那些可用主题
3. `omf install <theme>`：安装某个主题，也可以安装某些功能
4. `omf theme <theme>`：启动某个主题
5. `omf update`：更新框架主题与插件

### abbr缩写
快速创建一个命令缩写`abbr -a sl echo "lcz"`

这样在终端输入`sl+回车`，就会直接替换成`echo "lcz"`执行，如果`sl+空格`，就会替换成`echo "lcz"`且不执行，可以继续补充想要的指令

1. `abbr`：查看所有缩写
2. `abbr -a <缩写> '<完整命令>'`：创建新的缩写，例如：abbr -a gco 'git checkout'
3. `abbr -e <缩写>`： 删除指定缩写，例如：abbr -e gco

可以在配置文件中固化常用的缩写

类似的，可以使用`help abbr`在浏览器中打开窗口进行手册查阅