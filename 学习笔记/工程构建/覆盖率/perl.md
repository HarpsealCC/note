# perl

## 简介
Perl 是一种 解释型、动态、跨平台的编程语言，最初由 Larry Wall 于 1987 年开发。它被广泛应用于 系统管理、网络编程、文本处理、Web开发、自动化脚本 等领域。Perl 强调实用性和灵活性，常被称为 "瑞士军刀" 式的语言。


### 查看模块是否安装
- 已安装
```
$ perl -e "use JSON::XS; print 'JSON::XS is installed\n';"

JSON::XS is installed\n
```
- 未安装
```
$ perl -e "use Capture::Tiny; print 'Capture::Tiny is installed\n';"

Can't locate Capture/Tiny.pm in @INC (you may need to install the Capture::Tiny module) ...
```

### 安装缺少的模块

1. 使用cpan。

- 更新 cpan
```
sudo cpan App::cpanminus
```
- 安装模块
使用 cpan 安装每个模块：
```
sudo cpan Capture::Tiny DateTime Devel::Cover Digest::MD5 File::Spec JSON::XS Cpanel::JSON::XS JSON::PP JSON Memory::Process Module::Load::Conditional Scalar::Util Time::HiRes
```
- 验证安装
```
perl -e "use Capture::Tiny; print 'Capture::Tiny is installed\n';"
```

2. 使用 cpanminus
是一个更简洁的 Perl 模块管理工具，可以批量快速安装模块

- 安装 cpanminus：
```
sudo apt-get install cpanminus
```
- 批量安装常用模块：
```
sudo cpanm DateTime JSON LWP::UserAgent DBI XML::Simple Test::Simple
```
如果安装不上可以添加 `--force` 来强制安装

3. 去[meta::cpan网站](https://metacpan.org)搜索需要的模块，进行下载安装，[参考网站](https://zhuanlan.zhihu.com/p/161728028)。
e.g. 安装Date::Parser模块
- 访问网站，搜索需要的安装包

- 下载安装包

- 编译安装

    解压安装包Date-Parser-0.4.tar.gz
    ```
    $ tar -xvf Date-Parser-0.4.tar.gz
    ```
    进入到目录
    ```
    cd Date-Parser-0.4
    ```
    生成makefile, INSTALL_BASE可以指定安装目录
    ```
    perl Makefile.PL INSTALL_BASE=/home/perl_packge
    ```
    编译
    ```
    make
    ```
    安装
    ```
    make install
    ```

