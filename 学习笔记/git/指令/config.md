# 本文介绍git config指令

### 简介

Git 自带一个 git config 的工具来帮助设置控制 Git 外观和行为的配置变量。 在**linux**系统中这些变量存储在三个不同的位置：

`/etc/gitconfig` 文件: 包含系统上每一个用户及他们仓库的通用配置。 如果在执行 git config 时带上 --system 选项，那么它就会读写该文件中的配置变量。 （由于它是系统配置文件，因此你需要管理员或超级用户权限来修改它。）

`~/.gitconfig` 或 `~/.config/git/config` 文件：只针对当前用户。 你可以传递 --global 选项让 Git 读写此文件，这会对你系统上 所有 的仓库生效。

当前使用仓库的 Git 目录中的 config 文件（即 `.git/config`）：针对该仓库。 你可以传递 --local 选项让 Git 强制读写此文件，虽然默认情况下用的就是它。 （当然，你需要进入某个 Git 仓库中才能让该选项生效。）

每一个级别会覆盖上一级别的配置，所以 .git/config 的配置变量会覆盖 /etc/gitconfig 中的配置变量[^1]。如果在项目的 .git/config 文件中未设置某个配置项，Git 将会查找上一级别的配置文件[^2]。

[^1]: [《1.6 起步 - 初次运行 Git 前的配置》](https://git-scm.com/book/zh/v2/%E8%B5%B7%E6%AD%A5-%E5%88%9D%E6%AC%A1%E8%BF%90%E8%A1%8C-Git-%E5%89%8D%E7%9A%84%E9%85%8D%E7%BD%AE)
[^2]: 根据chatgpt的回答


### config查看
表示的是全局的配置
```
git config --list
git config -l
```

查看各个配置项来自的配置文件
```
git config --list --show-origin
```
查看具体的配置层级的参数列表
```
git config --[local|global|system] --list
```
### 配置信息

#### 用户信息(user.name user.email)
安装完 Git 之后，要做的第一件事就是设置你的用户名和邮件地址。 这一点很重要，因为每一个 Git 提交都会使用这些信息，它们会写入到你的每一次提交中，不可更改：
```
git config --global user.name "lcz"
git config --global user.email lcz@example.com
```

#### 文本编辑器(core.editor)
将默认编辑器修改为VS Code
```
git config --global core.editor "code -w"
```
设置成功会如下显示。
```
$ git config --global core.editor
code -w
```

#### ssh秘钥(core.sshcommand)
可以为单独的工程指定ssh的秘钥路径
```
git config core.sshCommand "ssh -i ~/.ssh/github_id1_rsa"
```


### 帮助
- `git config -h`
- `man git config`
- [gitconfig官网资料](https://git-scm.com/docs/git-config)
