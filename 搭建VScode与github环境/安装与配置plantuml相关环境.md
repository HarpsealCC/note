# 安装与配置plantuml相关环境

## 安装plantuml.jar
```
wget https://github.com/plantuml/plantuml/releases/download/v1.2023.13/plantuml-1.2023.13.jar
wget https://github.com/plantuml/plantuml/releases/download/v1.2023.13/plantuml-gplv2-1.2023.13.jar
```

## 安装Graphviz

```
sudo apt install graphviz  // 安装
dot -V  // 查看
```

## 配置markdown-preview-enhanced
在setting.josn中配置markdown-preview-enhanced.plantumlJarPath，需要路径中需要带jar包
如果找不到就重新加载一下vscode
```

```