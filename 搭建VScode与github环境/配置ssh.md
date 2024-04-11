# **配置节点的ssh指令**

## 本地配置多个git ssh连接的方法

### 前言
一般公司用的是自己内网部署的 gitlab 服务器进行代码管理，开发者使用的是公司的用户名和公司的邮箱，而在个人的开源项目中，我们的代码托管于 github，这个情况是不需要两个SSH-Key的，因为gitlab与github是网络隔离的，但是如果需要使用两个用户访问github或者gitlab，就需要进行其他配置。

### 方法一：使用ssh config进行配置
#### 第一步：查看所有 SSH-Key

打开 bash/zsh 终端：执行以下命令
```
$ cd ~/.ssh/
$ ls
```
#### 第二步：生成多个 ssh-key，用于配置公司的 GitLab与外部的GitHub
在~/.ssh/目录会生成gitlab_id_rsa和gitlab_id_rsa.pub私钥和公钥。
```
ssh-keygen -t rsa -C "xxx@xxx.com" -f ~/.ssh/github_id1_rsa
ssh-keygen -t rsa -C "xxx@xxx.com" -f ~/.ssh/github_id2_rsa
...
```
此时在~/.ssh下会产生两组文件
```
github_id1_rsa github_id2_rsa github_id1_rsa.pub github_id2_rsa.pub
```
#### 第三步：将公钥文件粘贴到GitLab或者GitHub上

一般都是在setting -> SSH and GPG keys中添加

#### 第四步：在 ~/.ssh 目录下添加config配置文件用于区分多个 SSH-Key
**1. 添加识别 SSH keys 新的私钥**
默认只读取 id_rsa，为了让 SSH 识别新的私钥，需要将新的私钥加入到 SSH agent 中
**查看已经添加的私钥**
```
ssh-add -l
```
**添加私钥**
```
$ ssh-agent bash
$ ssh-add ~/.ssh/github_id1_rsa
$ ssh-add ~/.ssh/github_id2_rsa
```

**2.添加 config 配置文件**

```
vi ~/.ssh/config
```
```
# 默认的 SSH 密钥
Host github1.com
  HostName github.com
  User git
  IdentityFile ~/.ssh/github_id1_rsa

# 另一个 Git 仓库使用的 SSH 密钥
Host github2.com
  HostName github.com
  User git
  IdentityFile ~/.ssh/github_id2_rsa
```
**config文件说明**
- **Host**：可以理解为对原Host github.com访问的别名，因为配置了多个github账户，所以不能同时用相同的host进行访问。
- **HostName**：原Host，如果访问github是不需要变化的。
- **User**： 一般也不需要变化。
- **IdentityFile**：私钥文件，配置之后Host就与私钥绑定。

需要注意config文件需要用户权限为600，且文件的owner要与执行git指令的用户一致
```
sudo chmod 600 /root/.ssh/config
sudo chown root:root /root/.ssh/config
```

#### 第五步：测试

如果没有配置多个账户，测试 github 外网 ssh 地址
```
ssh -T git@github.com
```
输出
```
Hi ***! You've successfully authenticated, but GitHub does not provide shell access
```

如果配置了多个账户，可以将github.com替换成config文件中写入的Host
**测试User1：**
```
ssh -T git@github1.com
```
输出
```
Hi User1! You've successfully authenticated, but GitHub does not provide shell access
```
**测试User2：**
```
ssh -T git@github2.com
```
输出
```
Hi User2! You've successfully authenticated, but GitHub does not provide shell access
```

#### 第六步：使用

配置之后，需要将**远程URL**更改为之前定义的别名
例如未配置时这么clone:
```
git clone git@github.com:cirrodata/fast-ap.git
```
配置后需要将`github.com`替换为`github1.com/github2.com`
```
git clone git@github1.com:cirrodata/fast-ap.git
```

### 方法二：为每个Git仓库配置不同的SSH密钥
不进行ssh config文件的编辑，改为在每个git仓库中(包含.git文件夹)执行以下指令
#### 第一步，第二步，第三步
生成不同的用户的私钥与公钥，同方法一

#### 第四步：配置git config
- 确认为仓库配置用户信息
```
git config user.name "Your Name"
git config user.email "your@email.com"
git config -l  // 查看
```
- 确认仓库的remote配置正常，**此种方法只能使用在git remote配置好的情况**
```
git remote add origin git@github.com:cirrodata/fast-ap.git
git remove -v  // 查看
```
- 配置sshCommand
```
git config core.sshCommand "ssh -i ~/.ssh/github_id1_rsa"
git config -l  // 查看
```
其中github_id1_rsa为生成的私钥文件

#### 第五步：使用

- 检查配置是否生效
```
git config -l  // 查看
```
输出
```
user.name=lcz
user.email=844291270@qq.com
safe.directory=/data1/workspace/liuchengzhuo/git/github/doris/be/src/apache-orc
safe.directory=/data1/workspace/liuchengzhuo/git/github/doris/be/src/clucene
core.repositoryformatversion=0
core.filemode=true
core.bare=false
core.logallrefupdates=true
core.sshcommand=ssh -i ~/.ssh/fastapgithub_id_rsa
remote.origin.url=git@github.com:cirrodata/fast-ap.git
remote.origin.fetch=+refs/heads/*:refs/remotes/origin/*
```
确认**remote sshcommand user**信息是否都配置

- 测试

```
[lcz@nn1 github]$ git config core.sshCommand "ssh -i ~/.ssh/notegithub_id_rsa"
[lcz@nn1 github]$ git pull git@github.com:cirrodata/fast-ap.git
ERROR: Repository not found.
fatal: Could not read from remote repository.

Please make sure you have the correct access rights
and the repository exists.
[lcz@nn1 github]$ git config core.sshCommand "ssh -i ~/.ssh/fastapgithub_id_rsa"
[lcz@nn1 github]$ git pull git@github.com:cirrodata/fast-ap.git
remote: Enumerating objects: 291496, done.
remote: Counting objects: 100% (63917/63917), done.
```
- 使用
可以直接访问远程url，不需要像config一样使用别名


## Windows下VSCode免密远程连接服务器

#### Windows下操作

- Win + R 键，输入PowerShell打开Window终端，输入下面命令生成密钥，三次询问均直接回车
```
ssh-keygen -t rsa -b 4096
```
- 上传公钥到远端

```
scp .\.ssh\id_rsa.pub 远端用户名@远端IP:~/
```
**注意**
若仍需输入密码,需修改用户目录权限不低于755(即数值不大于755)
```
chmod 755 /home/[usr_name]
```
#### 登录远端服务器操作
```
cat ~/id_rsa.pub >> ~/.ssh/authorized_keys
chmod 600 ~/.ssh/authorized_keys
```

### 问题

#### 1. 测试或者拉取代码时报Permission denied (publickey).
检查一下是不是忘记第三步了

#### 2. 测试或者拉取代码时报Bad owner or permissions on /root/.ssh/config.
全部报错信息如下：
```
Bad owner or permissions on /root/.ssh/config
fatal: Could not read from remote repository.

Please make sure you have the correct access rights
and the repository exists
```

如果是配置了一个后台访问不同的github账户，可以参考一下第二步

### 其他
参考网站
```
https://www.nhooo.com/note/qa3kj5.html
https://fengfuyuyang.github.io/2022/06/29/16/
```

git手册
```
https://git-scm.com/book/zh/v2
```

