# cmake学习笔记

## 安装

### 从源代码编译安装 CMake

- 下载 CMake 源代码：
```
wget https://cmake.org/files/v3.31/cmake-3.31.0.tar.gz
tar -zxvf cmake-3.31.0.tar.gz
cd cmake-3.31.0
```

- 编译并安装：

```
./bootstrap
make -j$(nproc)
sudo make install
```


### 使用 --classic 参数进行安装

```
sudo snap install cmake --classic
```


### 使用 PPA 安装 CMake

- 添加 PPA 仓库：
```
sudo apt update
sudo apt install -y software-properties-common
sudo add-apt-repository -y ppa:kitware/ppa
sudo apt update
```

- 安装 CMake：
```
sudo apt install cmake
```