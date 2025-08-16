# VMware虚拟机通过宿主机的v2ray进行外网访问

## 背景
在windows已经可以使用`v2rayN`进行外网访问的背景下，想要使虚拟机中的linux系统也可以进行外网访问，需要配置虚拟机中的网络代理。
## 前提条件
- 宿主机为windows系统，通过VMware开启了虚拟机
- 虚拟机能够通过宿主机访问网络，但是不能访问外网

## 配置VMware虚拟机代理

### 1. 确认宿主机 v2rayN设置
- 打开v2rayN ➡️ 参数设置 ➡️ 核心设置
- 确认：
    - 已勾选 **允许来自局域网的连接**
    - HTTP 代理端口（默认 10809）
    - SOCKS5 代理端口（默认 10808）

### 查宿主机IP
在宿主机执行`ipconfig`，找到VMware NAT的地址，例如 `192.168.52.1` 记住此IP，后面在虚拟机里要使用。
在执行玩`ipconfig`后，一般有 VMnet1/VMnet8两个结果，选择能够在虚拟机ping通的那个。

### 在虚拟机中配置代理
#### 在bash中配置：
```
export http_proxy="http://192.168.52.1:10809"
export https_proxy="http://192.168.52.1:10809"
export all_proxy="socks5://192.168.52.1:10808"
```
(可以写进 ~/.bashrc，永久生效)

#### 在系统设置中配置
如果是图形界面，以ubuntu为例，可以在settings ➡️ Network ➡️ VPN ➡️ Network Proxy中选择Manual选项进行配置，内容同上。

#### 注意
⚠️ 使用`v2rayN`时https_proxy注意不要配置成`https://192.168.52.1:10809`
- v2rayN 的 HTTP 代理端口（10809） 只支持 明文 HTTP CONNECT，不支持 SSL/TLS 握手。

- 写成 https://...，curl 就会尝试用 HTTPS over HTTPS proxy，结果对不上协议，握手直接断开 → unexpected eof while reading。


### 基础连通性测试
1. 测试 HTTP
```
curl -v http://www.google.com --proxy http://192.168.52.1:10809
```
2. 测试 HTTPS：
```
curl -v https://www.google.com --proxy http://192.168.147.1:10809
```
如果 HTTP 成功但 HTTPS 报错，多半是 DNS 污染 或 SSL 握手被干扰

### 修复 DNS 污染

编辑`/etc/resolv.conf`
```
nameserver 8.8.8.8
nameserver 1.1.1.1
```
重新测试：
```
nslookup github.com
```
如果返回了 GitHub 正常 IP
```
Server:         8.8.8.8
Address:        8.8.8.8#53

Non-authoritative answer:
Name:   github.com
Address: 20.205.243.166
```
说明 DNS OK。
### Git 专用代理设置
有时环境中的代理配置通了，但是git还是无法访问，可以给 git 单独加代理（避免用错环境变量）:
```
git config --global http.proxy http://192.168.52.1:10809
git config --global https.proxy http://192.168.52.1:10809
```
测试：
```
git ls-remote https://github.com/oh-my-fish/oh-my-fish.git
```
能返回 refs 就说明没问题。

### 防火墙检查（若仍不通）
- 关掉 Windows 防火墙，确认不是防火墙拦截。
- 如果关掉能用 → 给 v2rayN 的 10808/10809 开端口放行规则。

### ⚡ 最终顺序：
1. 宿主机 v2rayN 开局域网访问
2. 虚拟机代理指向宿主机 IP:端口
3. curl 测试 HTTP/HTTPS
4. 修 DNS
5. git 配置代理
6. 防火墙兜底