# **配置节点的ssh指令**

## 本地配置多个git ssh连接的方法

### 前言
一般公司用的是自己内网部署的 gitlab 服务器进行代码管理，开发者使用的是公司的用户名和公司的邮箱，而在个人的开源项目中，我们的代码托管于 github，这个情况是不需要两个SSH-Key的，因为gitlab与github是网络隔离的，但是如果需要使用两个用户访问github或者gitlab，就需要进行其他配置。

### 操作步骤
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

需要注意config文件需要用户权限为600，且文件的owner要与执行git指令的用户一致
```
sudo chmod 600 /root/.ssh/config
sudo chown root:root /root/.ssh/config
```

#### 第五步：测试

测试 github 外网 ssh 地址
```
ssh -T git@github.com
```
输出
```
Hi ***! You've successfully authenticated, but GitHub does not provide shell access
```

测试公司内网 ssh 地址
```
ssh -T git@xxxx.amazonaws.com.cn  // gitlab服务器地址
Welcome to GitLab, @***!
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
```

git手册
```
https://git-scm.com/book/zh/v2
```

