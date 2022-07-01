<!--
 * @Author: lcz lcz@git.com
 * @Date: 2022-06-28 14:12:06
 * @LastEditors: lcz lcz@git.com
 * @LastEditTime: 2022-07-01 16:42:18
 * @FilePath: /github/harpseal/东方国信工作资料/点查询/pageindex过滤相关功能.md
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
-->
# **本文记录在构思dp文件pageindex过滤功能的一些图示**


## 需求列表

```plantuml
@startmindmap

* dp索引查询优化
** 新增BloomFilter查询优化
*** 建表时需要指定表使用bloomfilter
*** insert时根据tupleschema在生成filemetadata时创建BloomFilter
*** 查询时需要根据filemetadata中有无BloomFilter进行决策
** 过滤条件下推
*** 过滤条件通过计划经scanxo下推到scanner
*** 需要对过滤条件进行解析
** 极值索引查询优化
*** insert时需要将极值写入到pageindex中，rowgroup&column级别的极值、page级别的极值
*** 需要将过滤条件进行下推
*** 对于极值索引过滤，先使用rowgroup&column级别的极值进行过滤，之后使用page级别的极值进行过滤
** 二分法或者遍历page页数据
*** 如果极值有升序或者降序的标志，可以启用二分查找
*** 没有排序标记就遍历
** 空column与page的提前过滤
*** insert需要在columnindex与pageindex里新增空column或空page的标记
*** scanner在进行实际io前需要根据空标记过滤要读取的数据范围
** 字典页的过滤
*** 如果此column中所有的page都使用字典编码，就可以使用字典页中的数据进行过滤
*** 否则不行

@endmindmap
```

## Scanner部分的运行流程

### open&addrange流程
```plantuml
@startmindmap
* open阶段
** 下推过滤条件解析
*** 过滤列具有单个过滤条件
**** 过滤条件与"is null"相关
**** 过滤条件与"is null"无关
*** 过滤列具有多个过滤条件
** 过滤列
*** 解析元数据
*** 列级别过滤
**** 判断空列
**** 列级别极值索引
**** bloomfilter
**** 使用字典过滤
*** page级别过滤
**** 判断空page
**** 极值过滤
***** 如果是有序极值，二分法
***** 如果是无序极值，遍历
**** 使用有效page计算有效行号，且addrange
** 查询列
*** 获取过滤列有效page的行号
*** 根据行号计算有效page，addrange
@endmindmap
```
### read流程
```plantuml
@startmindmap
* read阶段
** 获取mdp
** 读取过滤列
*** 过滤条件是is null
**** 空列或空page，读null值，但不实际读
**** 非空列或page，按照过滤好的page读即可
*** 过滤条件非is null，按照过滤好的page读即可
** 读取查询列
*** 读取后需要使用有效行号进行再次过滤
*** 遇到空page，读null值，但不实际读
** 将读取后的mdp交由llvm处理
@endmindmap
```
### 对于现有的有序表点查询优化逻辑的适配
```plantuml
@startmindmap
* 需要适配的方面
** inserter需要在parquet中对有序表的有序列新增极值存储顺序BoundaryOrder
** scanner需要使用二分法对page进行极值过滤
** 不局限于等值
** 在读取时
*** 原方案是在scanner中将过滤后的数据每个行数据都读取到mdp中，可以不需要llvm
*** 也可以考虑只过滤出page范围，数据读取后，交由llvm进行过滤
@endmindmap
```


## parquet文件中需要添加的元素
```plantuml
@startmindmap
* 需新增
** ColumnMetaData
*** 是否是空column
*** bloomfilter相关的标记
*** 极值存储顺序BoundaryOrder
** PageIndex
*** 是否是空page
@endmindmap
```