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
*** 需要对过滤条件进行解析*
** 极值索引查询优化
*** insert时需要将极值写入到filemetadata中，rowgroup&column级别的极值、page级别的极值
*** 对于极值索引过滤，先使用rowgroup&column级别的极值进行过滤，之后使用page级别的极值进行过滤
** 二分法或者遍历page页数据
*** 如果极值有升序或者降序的标志，可以启用二分查找
*** 没有排序标记就遍历
** 空column与page的提前过滤
*** insert需要在columnindex与pageindex里新增空column或空page的标记
*** scanner在进行实际io前需要根据空标记过滤要读取的数据范围
** 字典页的过滤
*** 如果此column中所有的page都使用字典编码，就可以使用字典页中的数据进行过滤


@endmindmap
```

## Scanner部分的运行流程

### open&addrange流程
```plantuml
@startmindmap
* open阶段
** 下推过滤条件解析
*** is null
*** 对node tree递归解析，只解析满足条件的node
*** 将解析后的条件分col记录
** 过滤列
*** 解析元数据
*** 构造过滤器
**** 不需要构造过滤器，全读
***** 一些开关或标志位
***** 无过滤条件

**** 需要构造列过滤器
***** rowgroup极值过滤
****** 构造rowgroup极值过滤器
***** 有无bloomfilter，是否等值
****** 构造bloom过滤器
***** 是否是全字典编码
****** 构造字典过滤器
***** page极值情况
****** 构造page极值过滤器
*** 列级别过滤
**** 判断空列
**** 列级别极值索引
**** bloomfilter--目前只支持等值
**** 使用字典过滤
*** page级别过滤
**** 判断空page
**** 极值过滤
***** 如果是有序极值，二分法
***** 如果是无序极值，遍历
**** 使用有效page计算有效行号，且addrange
** 查询列
*** 考虑空column的影响，考虑空page的影响，可以不用实际addrange
*** 获取过滤列有效page的行号根据行号计算有效page

@endmindmap
```
### read流程
```plantuml
@startmindmap
* read阶段
** 获取mdp
** 读取过滤列
*** 无过滤，全读
**** 考虑空column与空page
*** 有过滤，按照过滤好的page读即可
** 读取查询列
*** 无过滤，全读
**** 考虑空column与空page
*** 有过滤
**** 按照过滤列生成的有效行进行mdp对齐
**** 考虑空column与空page
** 将读取后的mdp交由llvm处理
@endmindmap
```



## parquet文件中需要添加的元素
```plantuml
@startmindmap
* 需新增
** rowgroup
*** 表示空column的vector
** ColumnMetaData
*** bloomfilter相关的标记
*** 极值存储顺序BoundaryOrder
*** 是否是全字典编码
*** 表示空page的vector

@endmindmap
```



```plantuml
@startyaml
col: result
a: 
    "<": 10
    "<=": 5
    ">=": 0
b:
    ">": 2
c:  
    "=": 1,2,3
@endyaml
```

```plantuml
@startyaml
col: result
a: 
    "<": 10
b:
    ">": 2
c:  
    "<": 1
@endyaml
```

## 一级模块关系图
```plantuml
@startuml
package "XOS" {
[ScanXo]
}
package "dpa" {
[DatapackScanner]
[DPScannerContext]
[RowGroup&pageFilter] #green

}
[ScanXo] --> [DPScannerContext] : add filter node 
[RowGroup&pageFilter] --> [DPScannerContext] : use DPFilterKey
[DatapackScanner] --> [RowGroup&pageFilter] : create and use bloom/dict/minmax filter
@enduml
```

# 运行视图

## 条件下推
```plantuml
@startuml

ScanXO -> DPScannerContext : 配置过滤条件到context
create DatapackScanner
ScanXO -> DatapackScanner : 传递context
create RowGroupFilter
DatapackScanner -> RowGroupFilter
DatapackScanner -> DatapackScanner : 读取filemetadata
DatapackScanner -> RowGroupFilter : 构建列过滤器
DatapackScanner -> DatapackScanner : 使用列过滤器进行过滤
DatapackScanner -> DatapackScanner : 进行col读取
create PageFilter
DatapackScanner -> PageFilter
DatapackScanner -> DatapackScanner :使用页过滤器进行过滤
==进行过滤列与扫描列数据读取==
@enduml
```
## 新增存储结构

```plantuml
@startuml

class DPFilterKey << (S,orchid) >>{
bool is_null；
int32_t filter_col_id_;
map<OperatorValue, vector<INode* >> op_and_value_;
bool DoFilterOptimization()
}
enum DPFilterType {
    ROWGROUP_BLOOM_FILTER = 0,
    ROWGROUP_DICT_FILTER,
    ROWGROUP_MINMAX_FILTER,
    ROWGROUP_NULL_FILTER,
    PAGE_MINMAX_FILTER,
    PAGE_NULL_FILTER
}
@enduml
```

## 新增的RowGroupFilter模块

```plantuml
@startuml
abstract class IRowGroupFilter {
{abstract} IRowGroupFilter()
{abstract} void RowGroupFilterProcess(vector<int>& rg_id）
{abstract} void Reset(parquet::FileMetaData* fmd，  std::vector<DPFilterKey> * dpfilterkey_list,IColumnScanner * colscanner)
{abstract} Bool NeedDoFilter()
#parquet::FileMetaData* file_meta_data_
#std::vector<DPFilterKey> * dpfilterkey_list_
#IColumnScanner * colscanner_
}

class BloomRowGroupFilter {
}

class MixMaxRowGroupFilter {
}

class DictRowGroupFilter {
}
class NullRowGroupFilter {
}

class RowGroupFilterFactory {
RowGroupFilterFactory()
IRowGroupFilter* CreateRowGroupFilter(DPFilterType filter_type)
parquet::FileMetaData* file_meta_data_
std::vector<DPFilterKey> * dpfilterkey_list_
}
RowGroupFilterFactory  --> IRowGroupFilter
BloomRowGroupFilter -up-|> IRowGroupFilter
DictRowGroupFilter -up-|> IRowGroupFilter
MixMaxRowGroupFilter -up-|> IRowGroupFilter
MixMaxRowGroupFilter -[hidden]-> DictRowGroupFilter
BloomRowGroupFilter -[hidden]-> MixMaxRowGroupFilter
NullRowGroupFilter -up-|> IRowGroupFilter
together {
    class BloomRowGroupFilter
    class MixMaxRowGroupFilter
    class DictRowGroupFilter
}
class DataPackScanner {
RowGroupFilterFactory rowgroup_filterfact_
}
class ParquetFileScanner {
void InitDictionaryFilter(const ColumnScannerAgent agent)
void InitBloomFilter(const ColumnScannerAgent agent)
Bool IsDictFilterable(const ColumnScannerAgent& agent)
Bool IsBloomFilterable(const ColumnScannerAgent& agent)
}
DataPackScanner --> RowGroupFilterFactory
IRowGroupFilter -up-> ParquetFileScanner
class IColumnScanner {
void InitDictionary(PhyLayer::IScanStream * stream, const parquet::ColumnChunk* colChunk)
bool IsNeedFilterByDict(DPFilterKey* filter)
}
class DictDecoder <<T>> {

}
ParquetFileScanner --> IColumnScanner
IColumnScanner --> DictDecoder
class MinMaxFilterHelper {

}
MixMaxRowGroupFilter --> MinMaxFilterHelper
@enduml
```

## 运行视图

```plantuml
@startuml
create DataPackScanner
create RowGroupFilterFactory

DataPackScanner -> RowGroupFilterFactory

DataPackScanner -> RowGroupFilterFactory : 创建过滤器工厂
loop MinMax&Bloom&Dict&Null Filter
create RowGroupFilter
RowGroupFilterFactory -> RowGroupFilter
DataPackScanner <- RowGroupFilterFactory : 返回实例CreateRowGroupFilter
DataPackScanner -> RowGroupFilter : reset filemetadata & dpfilter list
DataPackScanner -> RowGroupFilter : 判断是否需要进行过滤 NeedDoFilter()
DataPackScanner <- RowGroupFilter : 如果需要
DataPackScanner -> RowGroupFilter : 当前rowgroup进行过滤 RowGroupFilterProcess()
DataPackScanner <- RowGroupFilter : 返回过滤之后的rowgroup id list
==start column open==
end
@enduml
```


## 运行视图

```plantuml
@startuml
create DataPackScanner

create DictRowGroupFilter
DataPackScanner -> DictRowGroupFilter


DataPackScanner -> DictRowGroupFilter : NeedDoFilter
alt need filter
DataPackScanner -> DictRowGroupFilter : RowGroupFilterProcess
loop rowgroup
DataPackScanner -> BaseColumnScanner : InitDictionary 
activate BaseColumnScanner
BaseColumnScanner -> DictDecoder : load dict
deactivate BaseColumnScanner
DataPackScanner -> DictRowGroupFilter : RowGroupFilterProcess
DictRowGroupFilter -> BaseColumnScanner : IsNeedFilterByDict
activate BaseColumnScanner
BaseColumnScanner -> DictDecoder : DoDictFilter
BaseColumnScanner <- DictDecoder : return result


deactivate BaseColumnScanner
BaseColumnScanner -> DictRowGroupFilter : if filter
DictRowGroupFilter -> DataPackScanner :  if filter
deactivate BaseColumnScanner
end
end
@enduml
```

## 运行视图

```plantuml
@startuml
create DataPackScanner

create MinMaxRowGroupFilter
DataPackScanner -> MinMaxRowGroupFilter
create MinMaxFilterHelper
MinMaxRowGroupFilter -> MinMaxFilterHelper

DataPackScanner -> MinMaxRowGroupFilter : NeedDoFilter
alt need filter
DataPackScanner -> MinMaxRowGroupFilter : RowGroupFilterProcess
loop rowgroup
MinMaxRowGroupFilter -> MinMaxFilterHelper : ProcessMinMaxFilter 
MinMaxRowGroupFilter <- MinMaxFilterHelper : 是否需要过滤 
end
end
@enduml
```
## 运行视图

```plantuml
@startuml
create DataPackScanner

create NullRowGroupFilter
DataPackScanner -> NullRowGroupFilter

==start column open==

DataPackScanner -> NullRowGroupFilter : NeedDoFilter
alt need filter
DataPackScanner -> NullRowGroupFilter : RowGroupFilterProcess
loop rowgroup
NullRowGroupFilter -> NullRowGroupFilter: 是否需要过滤
end
end
@enduml
```

## 新增的PageFilter模块

```plantuml
@startuml
abstract class IPageFilter {
{abstract} IPageFilter()
{abstract} void Reset(parquet::ColumnMetaData* col_md， DPFilterKey* dpfilterkey)
{abstract} void PageFilterProcess(std::vector<std::pair<int64_t, int64_t>> )
{abstract} Bool NeedDoFilter()
#parquet::ColumnMetaData* col_md_
#DPFilterKey* dpfilter_key_
}

class MinMaxPageFilter {

}
class NullPageFilter {

}

MinMaxPageFilter -up-|> IPageFilter
NullPageFilter -up-|> IPageFilter
class PageFilterFactory {
PageFilterFactory()
IPageFilter* CreatePageFilter(DPFilterType filter_type)
parquet::ColumnMetaData* col_md_
DPFilterKey* dpfilter_key_
}

class ColumnScannerAgent {
IPageFilter* minmax_pagefilter_
vector<ValidPageRange> valid_page_range_
}

class ParquetFileScanner {
void ConfigFilterKey(std::vector<DPFilterKey> * dpfilterkey_list)
std::vector<std::pair<int, int>> GetColRange(const
 RowGroup & rowGroup, int idx， vector<int> valid_page_index)
std::vector<DPFilterKey> * dpfilterkey_list_
PageFilterFactory page_filterfact_
map<int, vector<pair<int,int>>> each_rowgroup_valid_rownum_range_
}
class ValidPageRangeIndex {
int valid_rownum
int startrowid_;
int endrowid_;
}
class ValidPageRange {
int row_growp_id
vector<pair<int,int>>> each_rowgroup_valid_page_range;
vector<ValidPageRangeIndex> valid_range_index
}
ParquetFileScanner --> PageFilterFactory
PageFilterFactory --> IPageFilter
ParquetFileScanner --> ColumnScannerAgent
ColumnScannerAgent --> ValidPageRange
ValidPageRange --> ValidPageRangeIndex
MinMaxPageFilter --> MinMaxFilterHelper
@enduml
```


## 运行视图

```plantuml
@startuml
create DatapackScanner
create ParquetFileScanner
DatapackScanner -> ParquetFileScanner : ConfigFilterKey
create ColumnScannerAgent
ParquetFileScanner -> ColumnScannerAgent
create stream
ColumnScannerAgent -> stream
create PageFilterFactory
ParquetFileScanner -> PageFilterFactory : Config & create

==start column open and add range ==
loop 每个列
ParquetFileScanner -> ParquetFileScanner : openColAgent()
activate ParquetFileScanner
ParquetFileScanner -> ParquetFileScanner : dofilter
activate ParquetFileScanner
alt 过滤列
create MinMaxPageFilter
PageFilterFactory -> MinMaxPageFilter
create MinMaxFilterHelper
MinMaxPageFilter -> MinMaxFilterHelper
ParquetFileScanner <- PageFilterFactory : MinMaxPageFilter
ParquetFileScanner -> ColumnScannerAgent : config MinMaxPageFilter
loop 每个rowgroup
activate ColumnScannerAgent
    ColumnScannerAgent -> MinMaxPageFilter : reset ColumnMetaData & dpfilterkey
    ColumnScannerAgent -> MinMaxPageFilter : NeedDoFilter
    alt 需要极值过滤
        ColumnScannerAgent -> MinMaxPageFilter : PageFilterProcess()
        MinMaxPageFilter -> MinMaxFilterHelper : ProcessMinMaxFilter
        MinMaxPageFilter <- MinMaxFilterHelper : if filter cur page
        ColumnScannerAgent <- MinMaxPageFilter : return filter_result,有效行范围
    end
end
end
deactivate ColumnScannerAgent
deactivate ParquetFileScanner





loop 每个rowgroup
ParquetFileScanner -> ParquetFileScanner : GenerateVaildPageRange()
activate ParquetFileScanner
deactivate ParquetFileScanner
ParquetFileScanner -> ColumnScannerAgent
activate ColumnScannerAgent
ColumnScannerAgent -> stream : addrange()
deactivate ColumnScannerAgent
end
deactivate ParquetFileScanner
end

@enduml
```


```plantuml
@startuml
create DataPackScanner
create ParquetFileScanner
DataPackScanner -> ParquetFileScanner

create ColumnScannerAgent
ParquetFileScanner -> ColumnScannerAgent
create stream
ColumnScannerAgent -> stream
loop rowgroup
DataPackScanner -> DataPackScanner : processData
activate DataPackScanner

==start filter column read ==
DataPackScanner -> ParquetFileScanner : readFilterCols()
activate ParquetFileScanner
loop 每个filter列
    ParquetFileScanner -> ColumnScannerAgent : GenerateSkipAndReadRange()
    ColumnScannerAgent -> stream : skip & read
    ParquetFileScanner <- stream : return mdp
end

DataPackScanner <- ParquetFileScanner : return  mdp
deactivate ParquetFileScanner
DataPackScanner -> LLVM : filter src mdp with llvm
DataPackScanner <- LLVM : return des mdp & filterRowIndex
==start scan column read ==
DataPackScanner -> ParquetFileScanner : readScanCols()
activate ParquetFileScanner
loop 每个scan列
    ParquetFileScanner -> ColumnScannerAgent : GenerateSkipAndReadRange()
    ColumnScannerAgent -> stream : skip & read
    ParquetFileScanner <- stream : return mdp
end
DataPackScanner <- ParquetFileScanner : return  mdp
end
deactivate ParquetFileScanner
deactivate DataPackScanner

@enduml
```


# 详设相关

## 公共数据类型
```plantuml
@startuml

class DPFilterKey << (S,orchid) >>{
bool is_null；
int32_t filter_col_id_;
map<OperatorValue, vector<INode* >> op_and_value_;
bool DoFilterOptimization()
}
class scan_xo {
Void internal_prepare()
}
class ScannerFactoryCreator {
Void GenerateDPFilterKey（std::vector<Model::INode*> *nodes,
 xcloud::TupleDesc* td, std::vector<DPFilterKey> dpfilterkey_list）
}

scan_xo --> ScannerFactoryCreator
ScannerFactoryCreator --> DPFilterKey
@enduml
```

## minmaxfilterhelper
```plantuml
@startuml
class MinMaxFilterHelper {
{static}bool ProcessMinMaxFilter(pair<string,string> min_max, DPFilterKey* filterkey)
typedef boost::function<bool (std::string, INode*) > MinMaxFilterFunctor;
{static}MinMaxFilterFunctor  func_generater_;
}
class CompareFuncGenerater  {
MinMaxFilterFunctor GetCompareFunc(OPType op_type，DataType data_type)
bool CompareLT<T>(std::string value, INode* value_node)
bool CompareGT<T>(std::string value, INode* value_node)
bool CompareEQ<T>(std::string value, INode* value_node)
}
enum OPType {
    EQ
    LT
    GT
}
MinMaxFilterHelper *-- "1" CompareFuncGenerater 
CompareFuncGenerater -left-> OPType
@enduml
```



```plantuml
@startmindmap

* OperatorNode：op_and
** leftnode
*** OperatorNode：op_gt
**** leftnode
***** colunm node
**** rightnode
***** value node
** rightnode
*** OperatorNode：op_lt
**** leftnode
***** colunm node
**** rightnode
***** value node
@endmindmap
```


