

```plantuml
@startuml
package "xcloud" {
[xcloudd] #grey
}

@enduml
```


# 第零层分解1

```plantuml
@startuml
package "hdfsa" {
[ClientCacheHdfs] - [HdfsAccessService]
}
package "hadoop" {
[HDFS]
}
package "datapack" {
[DataPackReader]
}
package "runprof" {
[RuntimeProfile]
}
package "GetJvmInfo.jar" {
[GetJvmInfo] - jvm
}
package "exec_xos" {
[ScanXo]
}
package "PhyLayer" {
[diskio] - [readercontext]
}
package "scanner" {
[mdpreader]
}
[ScanXo] --> [mdpreader]
[mdpreader] --> [DataPackReader]
[DataPackReader] --> [RuntimeProfile]
[readercontext]  --> [RuntimeProfile]
[HdfsAccessService] --> [HDFS]

[HdfsAccessService] -right-> [RuntimeProfile]
package "resource" {
[LocalResourceUsage]
}
[LocalResourceUsage] --> [ClientCacheHdfs]
[LocalResourceUsage] -up-> [GetJvmInfo]
[LocalResourceUsage] -left-> [glog] 

@enduml

```

# 第零层分解2

```plantuml
@startuml
package "cirrodata" {
[hdfsa] -- [runprof] : 使用counter计数
[exec_xos] - [scanner] : 调用scanner相关接口
[scanner] - [datapack] : 调用reader相关接口
[datapack] -- [PhyLayer] : 与diskio进行交互
[resource] -down- [runprof] : 使用counter计数
[PhyLayer] -down- [runprof] : 使用counter计数
}

package "hadoop" {
[HDFS]
}
package "GetJvmInfo.jar" {
[GetJvmInfo] - [jvm] : 获取jvm信息
}
[hdfsa] --> [HDFS] : hdfs api
[resource] -up-> [GetJvmInfo] : jni 获取jvm信息
@enduml

```





# 图例
```plantuml
@startuml


package "模块集合&" {
[新增模块]  #green 
[修改模块] 
[未修改模块] #grey

[新增模块] -right-> [修改模块] : 调用关系说明
[新增模块] -left-> [未修改模块] #grey : 接口未修改 
}
@enduml

```
# 第一级分解
```plantuml
@startuml

package "cirrodata" {
[JvmInfoCollector] #green
[glog] #grey
[ClientCacheHdfs] -> [HdfsAccessService]: Get Each HdfsIO Info api
[RuntimeProfile]
[LocalResourceUsage] -up-> [JvmInfoCollector] : GetJvmInfo api 
[LocalResourceUsage] -left-> [glog] : print log api 
}
package "hadoop" {
[HDFS] #grey
}

package "GetJvmInfo.jar" {
[GetJvmInfo] #green
[MemoryMXBean] #green
[MemoryPoolMXBean] #green
[ThreadMXBean] #green
[GetJvmInfo] -up-> [MemoryMXBean] : GetMemInfo api
[GetJvmInfo] -up-> [MemoryPoolMXBean] : GetMemInfo api
[GetJvmInfo] -up-> [ThreadMXBean] : GetThreadInfo api
}


[HdfsAccessService] --> [HDFS] :jni hdfs 
[HdfsAccessService] --> [RuntimeProfile] : 使用counter计数 api
[LocalResourceUsage] --> [ClientCacheHdfs] : Get Total Hdfsio Info
[JvmInfoCollector] -up-> [GetJvmInfo] : Jni GetMemInfo & GetThreadInfo api


@enduml

```

```plantuml
@startuml

package "exec_xos&scanner" {
[Scanxo] #grey
[Scanxo] -up-> [mdpreader] #grey : pass readercontext
}

package "datapack" {
[DatapackReader] --> [ParquetFileScanner] #grey : pass readercontext

}
package "PhyLayer" {
[readercontext] 
[DiskIoMgr] --> [ScanRange] : update readercontext
[ScanRange]
[ScanStream]
}
package "runprof" {
[RuntimeProfile] #grey
}

[mdpreader] -left-> [DatapackReader] #grey
[Scanxo] --> [readercontext] : create 

[ParquetFileScanner] --> [ScanStream] : Create & Init ScanStream pass readercontext
[ScanStream] --> [ScanRange] : Create ScanRange & Add readercontext

[ScanStream] --> [DiskIoMgr] #grey : Add ScanRange & readercontext

[readercontext] -left-> [RuntimeProfile] : contain

@enduml
```

# 运行视图

## 新增hdfsio相关统计信息日志功能相关模块
```plantuml
@startuml

LocalResourceUsage -> ClientCacheHdfs : 获取HdfsAccess信息
loop 本地hdfs+远端数量
    ClientCacheHdfs -> HDFSAssessService : 获取hdfsio信息
    HDFSAssessService -> Runtimeprofile : 使用counter进行统计
    HDFSAssessService -> ClientCacheHdfs : 返回消息
end
LocalResourceUsage <- ClientCacheHdfs : 返回消息
LocalResourceUsage -> glog : 输出到日志

@enduml
```
## 获取jvm内存与线程信息
```plantuml
@startuml

LocalResourceUsage -> JvmInfoCollector : 获取jvm内存与线程信息
box java
JvmInfoCollector -> GetJvmInfo : 通过jni调用GetJvmInfo中的信息

GetJvmInfo -> MemoryMXBean : 获取堆内存信息
GetJvmInfo -> MemoryPoolMXBean : 获取非堆内存信息
GetJvmInfo -> ThreadMXBean : 获取线程信息
end box
GetJvmInfo -> Protobuf : 序列化
GetJvmInfo -> JvmInfoCollector : 返回获取的内容

JvmInfoCollector -> Protobuf : 反序列化
JvmInfoCollector -> LocalResourceUsage : 返回信息
LocalResourceUsage -> glog : 输出到日志
@enduml
```

## 更新diskio相关的统计信息
```plantuml
@startuml

ScanXo -> Readercontext : use
Readercontext -> RuntimeProfile : use 
create mdpreader
ScanXo -> mdpreader : 传递Readercontext
create DatapackReader
mdpreader -> DatapackReader : 传递context
create ParquetFileScanner
DatapackReader -> ParquetFileScanner : 传递context
create ScanStream
ParquetFileScanner -> ScanStream 
ParquetFileScanner -> ScanStream : 传递context
create ScanRange
ScanStream  -> ScanRange
ScanStream  -> ScanRange : 传递context


ScanStream -> DiskioMgr : 添加ScanRange到diskiomgr

DiskioMgr -> ScanRange : 调用ScanRange
ScanRange -> ScanRange : 更新context
ScanRange -> ScanStream : 完成
ScanStream -> ParquetFileScanner :完成
ParquetFileScanner -> DatapackReader : 完成
DatapackReader -> mdpreader : 完成
mdpreader -> ScanXo : 完成
ScanXo -> ScanXo : Profile在执行器\n析构时统一处理
@enduml
```

# Protobuf数据格式
```plantuml
@startuml

class PGetJvmMemoryMetricsResponse  << (P,orchid) >> {
  repeated  PJvmMemoryPool memory_pools = 1;
  optional int64 gc_num_warn_threshold_exceeded = 2;  // useless
  optional int64 gc_num_info_threshold_exceeded = 3;  // useless
  optional int64 gc_total_extra_sleep_time_millis = 4;  // uesless
  optional int64 gc_count = 5;
  optional int64 gc_time_millis = 6;
}


class PJvmMemoryPool << (P,orchid) >>{
  optional int64 committed = 1;
  optional int64 init = 2;
  optional int64 max = 3;
  optional int64 used = 4;
  optional int64 peak_committed = 5;
  optional int64 peak_init = 6;
  optional int64 peak_max = 7;
  optional int64 peak_used = 8;
  optional string name = 9;
}
class PGetJvmThreadsInfoResponse << (P,orchid) >>{
    optional int32 total_thread_count = 1;
    optional int32 daemon_thread_count = 2;
    optional int32 peak_thread_count = 3;
    repeated  PJvmThreadInfo threads = 4;
}
class PJvmThreadInfo << (P,orchid) >>{
  optional string summary = 1;
  optional int64 cpu_time_in_ns = 2;
  optional int64 user_time_in_ns = 3;
  optional int64 blocked_count = 4;
  optional int64 blocked_time_in_ms = 5;
  optional bool is_in_native = 7;
}

@enduml
```
# Protobuf数据格式关系
```plantuml
@startuml

class PGetJvmMemoryMetricsResponse << (P,orchid) >> {
  repeated  PJvmMemoryPool memory_pools = 1;
  optional int64 gc_num_warn_threshold_exceeded = 2;  // useless
  optional int64 gc_num_info_threshold_exceeded = 3;  // useless
  optional int64 gc_total_extra_sleep_time_millis = 4;  // uesless
  optional int64 gc_count = 5;
  optional int64 gc_time_millis = 6;
}


class PJvmMemoryPool << (P,orchid) >>{
  optional int64 committed = 1;
  optional int64 init = 2;
  optional int64 max = 3;
  optional int64 used = 4;
  optional int64 peak_committed = 5;
  optional int64 peak_init = 6;
  optional int64 peak_max = 7;
  optional int64 peak_used = 8;
  optional string name = 9;
}
class PGetJvmThreadsInfoResponse << (P,orchid) >>{
    optional int32 total_thread_count = 1;
    optional int32 daemon_thread_count = 2;
    optional int32 peak_thread_count = 3;
    repeated  PJvmThreadInfo threads = 4;
}
class PJvmThreadInfo << (P,orchid) >>{
  optional string summary = 1;
  optional int64 cpu_time_in_ns = 2;
  optional int64 user_time_in_ns = 3;
  optional int64 blocked_count = 4;
  optional int64 blocked_time_in_ms = 5;
  optional bool is_in_native = 7;
}
class user {
}
PJvmMemoryPool *-- PGetJvmMemoryMetricsResponse

PJvmThreadInfo *-- PGetJvmThreadsInfoResponse

PGetJvmMemoryMetricsResponse *-- user
PGetJvmThreadsInfoResponse *-- user
@enduml
```
# ReaderContext数据

```plantuml
@startuml
class ReaderContext {
Counter* total_active_thread_concurrency_;
vector<counter*> total_active_thread_concurrency_vec_;
Counter* active_hdfs_read_thread_cnt_;
vector<counter*> active_hdfs_read_thread_vec_;
vector<counter*> readerdisk_byte_;
vector<counter*> readerdisk_time_;
}
@enduml
```

# 核心类子模块分解-HdfsAccessService子模块

```plantuml
@startuml
abstract class IHdfsAccessService {
{abstract} virtual std::string CollectHdfsProfile() = 0
}
class HdfsAccessService {
runprof::ObjectPool hdfs_objpool_;
std::unique_ptr<runprof::RuntimeProfile> hdfs_profile_
std::unordered_map <std::string, SummaryStatsCounter> counter_storage_;
void InitProfileMember();
void ResetHdfsProfile();
{abstract} virtual std::string CollectHdfsProfile();
}

class InvokerMgr {
runprof::RuntimeProfile::SummaryStatsCounter* total_timer_
void RegisteSummaryStatsCounter(SummaryStatsCounter* counter)
void UpdateTimer(runprof::MonotonicStopWatch watch_timer)
}
class Invoker {
runprof::MonotonicStopWatch watch_timer_;
Invoker(InvokerMgr* ivMgr, const char* func)
~Invoker()
}
class ClientCacheHdfs {
ClientCacheMap m_client_cache;
std::string GetHdfsIoProfileInfo(const Context::IServiceContext* context);
}
class MonotonicStopWatch {

}
class RuntimeProfile::SummaryStatsCounter {
void ResetCounter()
}
IHdfsAccessService <|-- HdfsAccessService

InvokerMgr <. Invoker
InvokerMgr --* HdfsAccessService
Invoker <. HdfsAccessService
MonotonicStopWatch <.. HdfsAccessService
HdfsAccessService --* ClientCacheHdfs
RuntimeProfile::SummaryStatsCounter --* HdfsAccessService
@enduml
```
## 统计接口调用信息
```plantuml
@startuml
activate user
activate HdfsAccessService
create SummaryStatsCounter
HdfsAccessService -> SummaryStatsCounter : create
deactivate HdfsAccessService
==create over==
user ->  HdfsAccessService : 调用hdfs接口，以read为例
activate HdfsAccessService
create MonotonicStopWatch
HdfsAccessService -> MonotonicStopWatch : create
HdfsAccessService -> MonotonicStopWatch : Start
activate MonotonicStopWatch
HdfsAccessService -> HdfsAccessService : 调用hdfs api

MonotonicStopWatch -> HdfsAccessService : Stop
deactivate MonotonicStopWatch

HdfsAccessService -> SummaryStatsCounter : 更新统计信息
activate SummaryStatsCounter
SummaryStatsCounter -> HdfsAccessService
deactivate SummaryStatsCounter
HdfsAccessService -> user : 调用完成

deactivate HdfsAccessService
@enduml
```

## 收集统计接口信息 
```plantuml
@startuml
ClientCacheHdfs -> HdfsAccessService : 收集信息
loop 各个接口的counter
    HdfsAccessService -> SummaryStatsCounter : 获取信息PrettyPrint
end
HdfsAccessService -> SummaryStatsCounter : reset信息，此部分有加锁操作

@enduml
```

# 使用Invoker&InvokerMgr统计所有接口调用信息

```plantuml
@startuml
activate user
create SummaryStatsCounter
activate HdfsAccessService
HdfsAccessService -> SummaryStatsCounter : create
create InvokerMgr
HdfsAccessService -> InvokerMgr : create
HdfsAccessService -> InvokerMgr : 注册counter 
activate InvokerMgr
InvokerMgr -> HdfsAccessService
deactivate InvokerMgr
deactivate HdfsAccessService 
==create over==
user -> HdfsAccessService : 调用任意接口(hdfs相关)
create Invoke

activate HdfsAccessService
HdfsAccessService -> Invoke : 创建，传入InvokerMgr

create MonotonicStopWatch
activate Invoke
Invoke -> MonotonicStopWatch : create 

activate MonotonicStopWatch
Invoke -> MonotonicStopWatch : start

HdfsAccessService -> HdfsAccessService : 调用hdfs api

HdfsAccessService -> Invoke : 析构
Invoke -> MonotonicStopWatch : stop
deactivate Invoke

MonotonicStopWatch -> InvokerMgr : Update counter
activate InvokerMgr
InvokerMgr -> SummaryStatsCounter : Update
activate SummaryStatsCounter
SummaryStatsCounter -> InvokerMgr : Update end
deactivate SummaryStatsCounter
InvokerMgr -> MonotonicStopWatch
deactivate InvokerMgr
deactivate MonotonicStopWatch

HdfsAccessService -> user : 调用完成
deactivate HdfsAccessService
participant InvokerMgr order 1
participant SummaryStatsCounter order 2
@enduml
```
# 核心类子模块分解-并发线程使用度指标

```plantuml
@startuml
package "GetJvmInfo.jar" {
class GetJvmInfo {
byte[] GetMemInfo()
byte[] GetThreadInfo()
}
class ThreadMXBean {
int	getThreadCount()
long getThreadCpuTime(long id)
long getThreadUserTime(long id)
long getBlockedCount()
long getBlockedTime()
}
class  MemoryPoolMXBean {
MemoryUsage getHeapMemoryUsage()
MemoryUsage getUsage()
MemoryUsage getPeakUsage()
string getName()
}
class MemoryMXBean {
MemoryUsage getHeapMemoryUsage()
MemoryUsage getNonHeapMemoryUsage()
}

class PGetJvmMemoryMetricsResponse << (P,orchid) >> {
  repeated  PJvmMemoryPool memory_pools = 1;
  optional int64 gc_num_warn_threshold_exceeded = 2;  // useless
  optional int64 gc_num_info_threshold_exceeded = 3;  // useless
  optional int64 gc_total_extra_sleep_time_millis = 4;  // uesless
  optional int64 gc_count = 5;
  optional int64 gc_time_millis = 6;
}


class PJvmMemoryPool << (P,orchid) >>{
  optional int64 committed = 1;
  optional int64 init = 2;
  optional int64 max = 3;
  optional int64 used = 4;
  optional int64 peak_committed = 5;
  optional int64 peak_init = 6;
  optional int64 peak_max = 7;
  optional int64 peak_used = 8;
  optional string name = 9;
}
class PGetJvmThreadsInfoResponse << (P,orchid) >>{
    optional int32 total_thread_count = 1;
    optional int32 daemon_thread_count = 2;
    optional int32 peak_thread_count = 3;
    repeated  PJvmThreadInfo threads = 4;
}
class PJvmThreadInfo << (P,orchid) >>{
  optional string summary = 1;
  optional int64 cpu_time_in_ns = 2;
  optional int64 user_time_in_ns = 3;
  optional int64 blocked_count = 4;
  optional int64 blocked_time_in_ms = 5;
  optional bool is_in_native = 7;
}
}
PJvmMemoryPool *-- PGetJvmMemoryMetricsResponse

PJvmThreadInfo *-- PGetJvmThreadsInfoResponse

PGetJvmMemoryMetricsResponse <.. GetJvmInfo
PGetJvmThreadsInfoResponse <.. GetJvmInfo
GetJvmInfo ..> ThreadMXBean
GetJvmInfo ..> MemoryMXBean
GetJvmInfo ..> MemoryPoolMXBean

package "cirrodate" {
class JvmInfoCollector {
string GetMemInfo()
string GetThreadInfo()
}
class HdfsIoInfo {
void GetHdfsIoInfo(const Context::IServiceContext* context)
std::string GetJvmInfo()
void LogHdfsUsage(std::string)
}
class LocalResourceUsage {
HdfsIoInfo m_hdfsioinfo
bool loadResourceInfo(void)
{static} bool logResourceUsage()         
}

LocalResourceUsage ..> HdfsIoInfo
HdfsIoInfo ..> JvmInfoCollector

JvmInfoCollector .> GetJvmInfo : jni
@enduml
```

# 并发线程使用度指标
```plantuml
@startuml

together  {
class ReaderContext {
Counter* total_active_thread_concurrency_;
vector<counter*> total_active_thread_concurrency_vec_;
Counter* active_hdfs_read_thread_cnt_;
vector<counter*> active_hdfs_read_thread_vec_;
std::map<int, int> real_diskmap_storage_;
void UpdateDiskBitMap(int diskid)
void setDiskStats(int diskNum, std::map<int, int> diskmap)
std::vector<Counter*>* readerdisk_byte;
std::vector<Counter*>* readerdisk_time;
}

class ScanStream {
ScanStream(MemContext*, DiskIOMgr* , IHdfsAccessService* , int64_t , Counter* , int64_t)
}
class DiskIoMgr {
std::atomic_int total_diskio_thread_count_
IScanStream* openScanStream(MemContext* ,IHdfsAccessService* , Counter*)
DiskQueue* getDiskQueuebyValue(int diskId)
}
class RuntimeProfile {
vector<Counter*>* AddBucketingCounters()
RuntimeProfile::Counter* AddSamplingCounter(
        const string& name, Counter* src_counter)
void StopPeriodicCounters()
}
class DiskQueue << (S,orchid) >>{

}
}


class ScanRange {
void SetIOWaitCounter(runprof::RuntimeProfile::Counter* counter)
}
ScanRange --* ScanStream
DiskIoMgr ..> ScanStream
DiskIoMgr ..> ScanRange
DiskIoMgr .> DiskQueue
ScanStream ..> ReaderContext
ReaderContext *-- RuntimeProfile
@enduml
```

# DiskioMgr更新ReaderContext调用接口
```plantuml
@startuml
activate user
activate ReaderContext
create ReaderContext
user -> ReaderContext : create
ReaderContext ->  ReaderContext : create counter

ReaderContext -> RuntimeProfile : AddBucketingCounters \nAddSamplingCounter
deactivate ReaderContext
==create ReaderContext over==
==开始执行数据扫描==
create ScanStream
user -> ScanStream  : set ReaderContext

activate ScanStream
create ScanRange
ScanStream -> ScanRange : add ReaderContext
activate DiskIoMgr
ScanStream -> DiskIoMgr : add ScanRange to DiskQueue
loop DiskQueue

DiskIoMgr -> ScanRange : start read
activate ScanRange

ScanRange -> ReaderContext : 更新ReaderContext对应的Counter
activate ReaderContext
ReaderContext -> ScanRange
deactivate ReaderContext
ScanRange -> DiskIoMgr : end read
deactivate ScanRange
end
deactivate DiskIoMgr
== 功能数据扫描完成==
ReaderContext -> RuntimeProfile : StopPeriodicCounters

user -> ReaderContext  : collect
activate ReaderContext
ReaderContext -> user : return profile info
deactivate ReaderContext
@enduml
```

# 按disk显示吞吐量

