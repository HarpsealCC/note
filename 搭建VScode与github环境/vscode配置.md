# vscode配置

### Vscode-终端字体突然间距变大的解决办法[^1]
- 打开设置-用户-功能-终端
- 搜索 Font Family
- 找到终端的Font Family
- 设置为 Consolas
[^1]:引用[《Vscode——终端字体突然间距变大的解决办法》](https://blog.csdn.net/Williamcsj/article/details/135866476)

### VSCode 终端中选择文本时自动复制
```
"terminal.integrated.copyOnSelection": true
```
### VSCode 终端改变颜色
```
"workbench.colorCustomizations" : {
    "terminal.foreground" : "#D3D7CF",
    "terminal.background" : "#2E3436"
},
```