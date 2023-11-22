<!--
 * @FilePath: /东方国信工作资料/带有bitshuffle编码压缩调研/对于行云使用bitshuffle编码的想法.md
 * @Author: harpseal
 * @Date: 2023-02-17 16:57:36
 * @LastEditTime: 2023-02-28 10:30:19
 * @email: 844291270@qq.com
-->

思维导图

```plantuml
@startmindmap
* 行云压缩+编码
++ snappy
+++ [dict + plain] & snappy
++ lz4
+++ [dict + plain] & lz4
+++ <s>dict & lz4 + plain & bitshufflelz4</s>
+++ [dict + plain] & bitshufflelz4
+++ plain & bitshufflelz4
++++ 对于double类型bitshuffle编码后压缩性不佳
++++ int long类型在完全乱序的情况下，bitshuffle编码后压缩性能好，在有规律重复情况下压缩性差
++++ 对于number类型，乱序不乱序都有不同程度的优化

@endmindmap
```

<br>
