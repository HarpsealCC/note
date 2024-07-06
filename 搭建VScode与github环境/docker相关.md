# docker相关
<!-- TODO: (lcz)  需要继续完善-->
## docker compose
示例： 使用doris:latest image 启动可以编译调试的docker容器·
```
version: '3.4'
services:
  doris-release2.1.3:
    container_name: doris-release2.1.3
    image: registry.cn-hangzhou.aliyuncs.com/harpseal-images/doris:build-env-for-2.0
    network_mode: "host"
    cap_add:
      - SYS_PTRACE
    security_opt:
      - seccomp:unconfined
    privileged: true
    environment:
      - TZ=Asia/Shanghai
    volumes:
      - /home/harpseal/.ssh:/root/.ssh
      - /home/harpseal/github/doris:/root/doris
      - /home/harpseal/.m2:/root/.m2
      - /etc/localtime:/etc/localtime:ro
    working_dir: /root/3.5
    command: /bin/bash -c "\
      cd /root && \
      wget --no-check-certificate https://ftp.gnu.org/gnu/glibc/glibc-2.18.tar.gz && \
      tar xvfz glibc-2.18.tar.gz && \
      mkdir -p glibc-2.18/build && \
      cd glibc-2.18/build && \
      export CC=/usr/bin/gcc && \
      ../configure --prefix=/usr --disable-profile --enable-add-ons --with-headers=/usr/include --with-binutils=/usr/bin && \
      make -j5 && \
      make install && \
      yum install -y https://repo.ius.io/ius-release-el7.rpm https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm && \
      yum remove git -y && \
      yum install -y git236 bash-completion && \
      yum clean all && \
      rm -rf /root/glibc-2.18* /var/cache/yum && \
      tail -f /dev/null"
```

## docker pull 超时报错 "error pulling image configuration..."

问题： 使用docker拉取服务时出现报错
```
error pulling image configuration: download failed after attempts=6: dial tcp 31.13.83.34:443: i/o timeout
```

解决方案：
```
sudo mkdir -p /etc/docker
sudo tee /etc/docker/daemon.json <<-'EOF'
{
  "registry-mirrors": ["https://yxzrazem.mirror.aliyuncs.com"]
}
EOF
sudo systemctl daemon-reload
sudo systemctl restart docker
```


## Ubuntu安装docker(APT安装)

https://zhuanlan.zhihu.com/p/693926230

## docker迁移安装路径

https://www.cnblogs.com/chenss15060100790/p/18202920

wsl上目前有backingFsBlockDev文件无法迁移

## 解决docker无法正常pull 2024年6月13日
可能是被墙了，导致此时docker镜像无法正常pull，可以使用方法
https://github.com/bogeit/docker_image_pusher
进行操作
视频链接
https://t.bilibili.com/942173077475688457?share_source=pc_native