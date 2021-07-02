# **本文记录impala的查询方案的调研结果**

## **调研范围**
调研impala根据where过滤条件在scanner工作期间对page或者row-group的过滤方法。此外where的过滤条件的优化或者columnscanner的优化不在此次讨论的范围之内。

## **scanner的启动情况**
见博客图示

![scanner启动](./picture/hdfsscannode介绍.png)


## **parquet-scanner的行为**
见博客图示

![scanner启动](./picture/hdfsparquetscanner.png)


## **parquet-scanner对page的过滤操作**
```plantuml
@startmindmap
*:读取filemetadata page-index
page-location等信息
并且按照row-group进行遍历;
**:对当前loop的row-group进行
检查非法的就跳过
有错误就停止;
**:过滤的准备
读取row-group中每个column的极值;
**:第一步过滤
根据下推条件中的极值
对每个column进行过滤;
***:查询范围不正确
直接跳过;
***:column中的所有值都为null
直接跳过;
***:计算出的overlap_ratio为0.0
直接跳过;
****:overlap_ratio推测应该是
row-group的极值对filter-range的
覆盖范围。如果值为0.0，就是说
row-group的极值完全没有在filter-range内
threshold表示阈值，与overlap_ratio进行比较
通常表示当前row-group需不需要使用page页过滤和
llvm行过滤(?);
**:第二步过滤
读取每个PageIndex
根据下推条件中的极值
对每个page进行过滤
计算出每个column的
哪些page是可以被读取的;
***:先判定page-index是可读的状态之后
根据min_max_conjunct_evals获取需要的
colunmid，根据id读取该column所有的page的
row-range，放入skip_ranges等待过滤;
***:对skip-ranges进行过滤：
将空的page首先进行过滤
之后根据极值对page过滤;
****:二分查找:
fast code path mode为on状态
列内的page的最大值与最小值是有序的;
*****:如果列是内置类型
直接二分法;
*****:如果列非内置类型;
将数据转换成内置类型
再二分;
****:非二分查找：
根据极值对每个page进行过滤;
***:最后根据得出的过滤page
计算有效page范围并且
赋值给每个列的reader;
**:第三步过滤
对每个colunm使用布隆过滤器进行过滤;
***:布隆过滤器的构建只针对内部类型
TINYINT SMALLINT INT BIGINT 
FLOAT DOUBLE BYTE_ARRAY;
***:对等值过滤条件来进行构建的
如果下推min_max_conjunct_evals中
有LE与GE的值为同一个，就构建布隆过滤器;
**:进行文件内容的读取
每个scolumn按照过滤好的page id进行文件读取;
**:文件读取之后还要进行
最后的llvm的过滤;
***:bool类型的过滤可能
与普通类型具有不同的过滤方案
但是还不确定;
***:其他的类型就只使用
llvm的过滤函数进行过滤;
@endmindmap

```

```plantuml
@startmindmap
* 以row-group为单位进行读取
** 第一步，根据下推的条件初始化过滤函数与极值
** 第二步，根据极值过滤非法column
** 第三步，对合法的column的page使用极值继续进行过滤
** 第四步，对结果column使用布隆过滤器进行过滤
** 第五步，根据过滤结果按page范围进行数据读取
** 最后，将读取的数据交由llvm进行最后过滤
@endmindmap
```


```plantuml
@startuml

ExecNode <|-- ScanNode
ScanNode <|-- HdfsScanNodeBase
HdfsScanNodeBase <|-- HdfsScanNode
HdfsScanNodeBase <|-- HdfsScanNodeMt

@enduml

```

```plantuml
@startuml

class HdfsScanner {
    Status Open()
    Status ProcessSplit()
    Status CommitRows()
    Status GetNext()
    bool EvalConjuncts()
}
class HdfsParquetScanner {
    Status GetNextInternal()
    Status NextRowGroup()
    Status EvaluateStatsConjuncts()
    Status EvaluateOverlapForRowGroup()
    Status ProcessPageIndex()
    Status ProcessBloomFilter()
    Status EvalDictionaryFilters()
}

HdfsScanner <|-- HdfsParquetScanner

@enduml

```

```plantuml
@startuml
:根据下推条件获取需要过滤的column id;
:根据id读取每个colunm的page范围到row-page;
:遍历下推条件中的值，对row-page进行过滤;
while (遍历完成？) is (未完成)
    :过滤row-page中page为空的范围;
    :对剩下有效的page进行过滤;
    if (是否可以二分法过滤) then (yes)
        :二分法过滤;
    else (no)
        :遍历过滤;
    endif
endwhile (完成)
:过滤结果为skip-range;
:根据skip-range计算出每个column-reader应该读取的page范围;
:page过滤完成;
@enduml
```