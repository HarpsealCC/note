# docker相关

## docker compose
示例： 使用doris:latest image 启动可以编译调试的docker容器
```
version: '3.4'
services:
  olap-3.5:
    container_name: lcz-olap-3.5
    image: 172.16.44.50:2345/doris:latest
    network_mode: "host"
    cap_add:
      - SYS_PTRACE
    security_opt:
      - seccomp:unconfined
    privileged: true
    environment:
      - TZ=Asia/Shanghai
    volumes:
      - /home/lcz/.ssh:/root/.ssh
      - /home/lcz/.bashrc:/root/.bashrc
      - /home/lcz/.vscode-server:/root/.vscode-server
      - /data09/workspace/lcz/3.5:/root/3.5
      - /data09/workspace/lcz/.m2:/root/.m2
      - /data09/workspace/lcz/jdbc_drivers:/root/3.5/output/be/jdbc_drivers
      - /data09/workspace/lcz/settings.xml:/usr/share/maven/conf/settings.xml
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