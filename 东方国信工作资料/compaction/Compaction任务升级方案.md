任务升级方案思维导图
```plantuml
@startmindmap
* 任务升级功能
++ 功能执行方法
+++ 采用GMC指令进行在线升级
+++ 使用离线工具进行离线升级
++ 需要实现的功能
+++ 将重构前的任务升级到新的任务系统中
+++ 清理重构前的任务
+++[#pink] 任务升级后取消升级
++++ 在线升级此功能无法实现
++++ 离线工具
+++++ 重启之后就无法进行取消
+++++ 升级之后没有启动节点这个功能可以做
++++++ 需要判断是否重启过
+++[#pink] 任务降级
++++ 回退到重构前的任务系统执行
+++++ 只要旧的任务就可以
++++++ 只要旧任务文件没有被清理就可以直接用
+++++ 新的任务也一并降级 
++++ 就是要在新的任务系统下进行降级
+++++ 只要旧的任务就可以
++++++ 与取消升级一样
+++++ 新的任务也一并降级
@endmindmap
```
<br>

任务升级方案思维导图
```plantuml
@startmindmap
* 任务功能
++ 需要实现的功能
+++ 任务升级
++++ 将重构前的任务升级到新的任务系统中
++++ 清理重构前的任务
++++ 升级中断后通过再次执行可以继续升级
+++[#pink] 任务降级
++++ 将重构后的任务降级到旧任务系统中
++++ 清理重构后的任务
++++ 降级中断后通过再次执行可以继续降级
++ 功能执行方法
+++ 采用GMC指令进行在线升级
+++ 使用离线工具进行离线升级
@endmindmap
```
<br>

重构前的任务文件目录结构
```plantuml
@startsalt
{
{T
 + <color:red>cluster.compact
 ++ Compaction
 +++ Scheduler
 ++++ compct.xcloud24_9876.0.1617693156000 (init状态任务1)
 ++++ compct.xcloud24_9876.0.1617606756000.Assigned (Assigned状态任务2)
 ++++ compct.xcloud24_9876.0.1614928356000.Cancel (Cancel状态任务3)
 ++++ compct.xcloud24_9876.0.1583392356000.Done (Done状态任务4)
 +++ TaskAssigned
 ++++ xcloud24_9876
 +++++ compct.xcloud24_9876.1.1617606756000
 ++++++ Status.Success
 ++++++ TaskInfo
 +++++ xcloud25_9876
 ++++++ .....
 ++++ .....
}
}
@endsalt
```
<br>

升级之后预期的任务文件目录结构
```plantuml
@startsalt
{
{T
 + <color:red>cluster.compact
 ++ Compaction
 +++ Scheduler
 ++++ compct.xcloud24_9876.0.1617693156000 (init状态任务1)
 ++++ compct.xcloud24_9876.0.1617606756000.Assigned (Assigned状态任务2)
 ++++ compct.xcloud24_9876.0.1614928356000.Cancel (Cancel状态任务3)
 ++++ compct.xcloud24_9876.0.1583392356000.Done (Done状态任务4)
 +++ TaskAssigned
 ++++ xcloud24_9876
 +++++ compct.xcloud24_9876.1.1617606756000
 ++++++ Status.Success
 ++++++ TaskInfo
 +++++ xcloud25_9876
 ++++++ .....
 ++++ .....
 ++ Compation_V2
 +++ TaskUpgrade.done（任务全部升级完成标志）
 +++ Scheduler
 ++++ aaaaffff.16176931.56000000.0 (升级后的任务1)
 +++++ Status.Init
 +++++ TaskInfo.pc.db
 ++++ aaaaffff.16176067.56000000.0 (升级后的任务2)
 +++++ Status.Init
 +++++ TaskInfo.pc.db
 ++++ aaaaffff.16149283.56000000.0 (升级后的任务3)
 +++++ Status.Cancel
 +++++ TaskInfo.pc.db
 ++++ aaaaffff.15833923.56000000.0 (升级后的任务4)
 +++++ Status.Done
 +++++ TaskInfo.pc.db
 +++ TaskAssigned
 ++++ xcloud24_9876
 +++++ ....
}
}
@endsalt
```
<br>

```plantuml
@startuml

start
:程序启动;
:确定行云进程状态;
:添加任务锁，只允许一个节点进行任务升级;
:开始升级任务;
if(所有任务全部升级完成？) then(yes)
:提示所有任务已经升级完成;
stop
else (no)
    :获取旧任务文件列表;
    if(文件列表为空？) then (yes)
    :提示没有任务需要升级;
    stop
    else (no)
        repeat:进行升级 
            if (该任务是否升级完毕?) then (yes)
            else (no)
                : *升级任务;
            endif
            backward:下一个任务文件;
        repeat while (是否是最后一个文件?)is(no) not(yes)
    :全部任务升级完成;
    :解除任务锁，任务升级结束;
    stop

@enduml
```
<br>

任务升级具体文件操作
```plantuml
@startuml

start

if(是否上次升级失败)then(yes)
:读取标志文件上的节点信息;
:清除上次升级遗留的文件; 
else(no)
endif
:读取旧任务信息;
:通过schema获取pc;
if(PC合法？)then(no) 
    :cancel任务;
    stop
else(yes)
    :创建出标志文件，后缀为任务执行节点信息;
    :创建任务的managerfile;
    :创建任务的maintaskinfo;
    :将标志文件重命名，后缀为upgrade;
    
stop

@enduml
```
<br>

下发升级指令前,假设有两个任务需要升级
```plantuml
@startsalt
{
{T
 + <color:red>cluster.compact
 ++ Compaction
 +++ Scheduler
 ++++ compct.xcloud24_9876.0.1617693156000
 ++++ compct.xcloud24_9876.0.1617606756000
 +++ TaskAssigned
 ++++ xcloud24_9876
 ++ Compaction_V2
 +++ Scheduler
 +++ TaskAssigned
}
}
@endsalt
```
<br>

需要创建读写锁保证只有一个节点操作（使用离线工具可以不用考虑？）
```plantuml
@startsalt
{
{T
 + <color:red>cluster.compact
 ++ Compaction
 +++ Scheduler
 ++++ compct.xcloud24_9876.0.1617693156000 
 ++++ compct.xcloud24_9876.0.1617606756000
 +++ TaskAssigned
 ++++ xcloud24_9876
 ++ Compaction_V2
 +++ TaskupgradeLock（读写锁，避免其他节点同时操作）
 +++ Scheduler
 +++ TaskAssigned
}
}
@endsalt
```
<br>

升级任务1，读取任务，在新的任务系统中添加新的任务文件，任务文件升级之后
添加标志表示该任务升级完成，这是为了保证升级过程中如果有某个任务失败，再次下发升级命令
可以跳过已经升级完成的任务继续升级
```plantuml
@startsalt
{
{T
 + <color:red>cluster.compact
 ++ Compaction
 +++ Scheduler
 ++++ compct.xcloud24_9876.0.1617693156000 （升级任务1）
 ++++ compct.xcloud24_9876.0.1617606756000
 +++ TaskAssigned
 ++++ xcloud24_9876
 ++ Compaction_V2
 +++ TaskupgradeLock
 +++ Taskupgrade
 ++++ compct.xcloud24_9876.0.1617693156000.upgrade (任务升级后添加完成标志)
 +++ Scheduler
 ++++ aaaaffff.16176931.56000000.0 （升级之后的任务文件）
 +++++ Status.Init
 +++++ TaskInfo.pc.db
 +++ TaskAssigned
}
}
@endsalt
```
<br>

全部任务都升级完成以后，先将小的标志位去掉，之后将Taskupgrade改为Taskupgrade.done
表示升级全部完成，之后再下发升级指令，检测到这个标志之后就不进行升级
最后删除TaskupgradeLock这个读写锁
```plantuml
@startsalt
{
{T
 + <color:red>cluster.compact
 ++ Compaction
 +++ Scheduler
 ++++ compct.xcloud24_9876.0.1617693156000 （升级任务1）
 ++++ compct.xcloud24_9876.0.1617606756000 （升级任务2）
 +++ TaskAssigned
 ++++ xcloud24_9876
 ++ Compaction_V2
 +++ <s>TaskupgradeLock</s>
 +++ <s>Taskupgrade</s> =>  Taskgrade.done
 ++++ <s>compct.xcloud24_9876.0.1617693156000.upgrade (任务升级后添加完成标志)
 ++++ <s>compct.xcloud24_9876.0.1617606756000.upgrade（任务升级后添加完成标志）
 +++ Scheduler
 ++++ aaaaffff.16176931.56000000.0 （升级之后的任务文件）
 +++++ Status.Init
 +++++ TaskInfo.pc.db
 ++++ aaaaffff.16176067.56000000.0 （升级之后的任务文件）
 +++++ Status.Init
 +++++ TaskInfo.pc.db
 +++ TaskAssigned
}
}
@endsalt
```
<br>

删除指令将原始的任务文件以及一些辅助的标志文件删除
```plantuml
@startsalt
{
{T
 + <color:red>cluster.compact
 ++ <s>Compaction
 +++ <s>Scheduler
 ++++ <s>compct.xcloud24_9876.0.1617693156000 (init状态任务1)
 ++++ <s>compct.xcloud24_9876.0.1617606756000.Assigned (Assigned状态任务2)
 ++++ <s>compct.xcloud24_9876.0.1614928356000.Cancel (Cancel状态任务3)
 ++++ <s>compct.xcloud24_9876.0.1583392356000.Done (Done状态任务4)
 +++ <s>TaskAssigned
 ++++ <s>xcloud24_9876
 +++++ <s>compct.xcloud24_9876.1.1617606756000
 ++++++ <s>Status.Success
 ++++++ <s>TaskInfo
 +++++ <s>xcloud25_9876
 ++++++ .....
 ++++ .....
 ++ Compation_V2
 +++ <s>TaskUpgrade.done（任务全部升级完成标志）
 +++ Scheduler
 ++++ aaaaffff.16176931.56000000.0 (升级后的任务1)
 +++++ Status.Init
 +++++ TaskInfo.pc.db
 ++++ aaaaffff.16176067.56000000.0 (升级后的任务2)
 +++++ Status.Init
 +++++ TaskInfo.pc.db
 ++++ aaaaffff.16149283.56000000.0 (升级后的任务3)
 +++++ Status.Cancel
 +++++ TaskInfo.pc.db
 ++++ aaaaffff.15833923.56000000.0 (升级后的任务4)
 +++++ Status.Done
 +++++ TaskInfo.pc.db
 +++ TaskAssigned
 ++++ xcloud24_9876
 +++++ ....
}
}
@endsalt
```
<br>

升级任务后PC信息的指定方式
```plantuml
@startmindmap
* PC信息的指定方式
++ 通过schema查询PC来使用资源
+++ schema有单个PC的权限
++++ 使用该PC来执行任务
+++ schema有多PC的权限
++++ 随机选取一个PC来执行任务
+++ schema没有PC的权限
++++ 集群存在PC
+++++ 该任务cancel
++++ 集群不存在pc
+++++ 可以使用所有节点资源
+++ 查询不到schema
++++ 任务cancel

++[#pink] 通过入口节点所在的PC来分配资源
+++ 入口节点被分配到进程组
++++ 使用该进程组资源执行
+++ 入口节点未被分配的进程组
++++ 使用未分配到进程组的资源执行
+++ 入口节点被卸载
++++ 任务被cancel
++++ 希望继续执行，任务被重分配
@endmindmap
```
<br>

任务升级方案思维导图
```plantuml
@startmindmap
* 任务功能
++ 需要实现的功能
+++ 任务升级
++++ 将重构前的任务升级到新的任务系统中
++++ 清理重构前的任务
++++ 升级中断后通过再次执行可以继续升级

++ 功能执行方法
+++ 采用GMC指令进行在线升级
+++ 使用离线工具进行离线升级
@endmindmap
```
<br>

旧任务内容：
```plantuml
@startyaml
CompactTaskId: "taskid"
CompactTaskState: "state"
bool: repeat_flag
bool: sub_task_flag
RepeatInfo: 
	int: repeatCount
	int: repeatInterval
ResultInfo:
	int: successCount
	int: failedCount
string: db_name
string: schema_name
string: table_name
string: partition_name
@endyaml
```
<br>

新任务内容：
```plantuml
@startyaml
CompactTaskId: "taskid" (任务id需要进行修改) 
CompactTaskState: "state"
bool: repeat_flag
bool: sub_task_flag
bool: sync_task_flag（新元素，升级而来的任务都是false）
CompactOptimization:
	string:db_name（新元素）
	string:pc_name（新元素）
RepeatInfo: 
	int: repeatCount
	int: repeatInterval
ResultInfo:
	int: successCount
	int: failedCount
string: db_name
string: schema_name
string: table_name
string: partition_name
string: pc_name （新元素，需要指定）  
@endyaml
```

<br>

任务升级失败方案思维导图
```plantuml
@startmindmap
* 任务执行
++ 任务执行失败
+++ 在读取时失败
++++ 无影响
+++ 在创建mgrfile过程或之后失败
++++ 再次执行时
+++++ id有对照关系的话就删除
+++++ id没有对照关系的话系统可以自己解决
+++ 创建mgrfile成功但是创建maininfo失败
++++ 可以删除之后再创建

@endmindmap
<br>

```plantuml
@startuml
package "cirrodata" {
[cirrodata-tool] as tool
}
package "hadoop" {
[HDFS] as hdfs
}

package "metadata" {
[HDFSMetaQueryProxy] as	Meta
}

[Zookeeper] as zookeeper
tool ..> hdfs:use hdfs api
tool ..> zookeeper:use zookeeper api
tool .> Meta : use metadata api
shell .. tool
@enduml
```
<br>

```plantuml
@startuml
package "cirrodata" {
[cirrdatatool-compaction-upgrade] as upgrade
[PUCtrl] as PUCtrl
[Compactionfilehelper] as filehelper
[zkadapter] as zkadapter
[HdfsAccessService] as hdfsa
[MetaDataService] as metaservice
hdfs_operation - hdfsa  
filehelper - hdfs_operation
upgrade -- file_operation
file_operation -- filehelper
get_puinfo - upgrade
PUCtrl - get_puinfo
zkhelp -- PUCtrl
zkadapter -- zkhelp 
zkadapter -- zklock
zklock -- upgrade
metaservice -- get_table_info
get_table_info -- upgrade
}
package "hadoop" {
[HDFS] as hdfs
}
package "metadata" {
[HDFSMetaQueryProxy] as	Meta
}
[Zookeeper] as zookeeper
hdfs <.. hdfsa :use hdfs api
zookeeper <.. zkadapter :use zookeeper api
Meta <.. metaservice: use meta service api
upgrade . shell
@endum
```
<br>

启动离线工具进行任务升级
```plantuml
@startuml
用户-> cirrodatatool : 启动工具
cirrodatatool -> Compactionfilehelper : 检测是否进行升级
cirrodatatool <- Compactionfilehelper : 反馈检测结果
cirrodatatool -> zkadapter : 添加锁
cirrodatatool -> Compactionfilehelper : 获取待升级的文件列表
cirrodatatool <- Compactionfilehelper : 反馈结果
loop 文件个数
    cirrodatatool -> Compactionfilehelper : 进行任务文件升级
	cirrodatatool -> MetaDataServiece : 查询schema信息
end
cirrodatatool -> Compactionfilehelper : 全部任务文件升级完成
cirrodatatool -> zkadapter : 取消锁
用户 <- cirrodatatool : 反馈任务完成
@enduml
```

<br>

启动离线工具进行任务删除
```plantuml
@startuml
用户-> cirrodatatool : 启动工具
cirrodatatool -> zkadapter : 添加锁
cirrodatatool -> Compactionfilehelper : 删除旧任务文件
cirrodatatool -> zkadapter : 取消锁
用户 <- cirrodatatool : 反馈任务完成
@enduml
```
<br>

cirrdatatool-compaction-upgrade二级模块
```plantuml
@startuml
skinparam classAttributeIconSize 0
class ToolDispatch {
    +void Dispatch(const std::string tool_name)
}
abstract class ToolAdapter {
    {abstract}void Init()
    {abstract}void Excu()
    {abstract}void Release()
}
class ComptaskUpgradeAdapter {
    +void Init()
    +void Excu()
    +void Release()
    -void Excute(TaskUpgrade, OP_TYPE)
    -  checkOptition(std::string op)
    -bool CheckAllOffline()
    -void ShowUsage()
    -void SetLock()
    -void ReleaseLock()
}
class TaskUpgrade {
    +void UpdateTaskFromOld()
    +void DeleteOldTask()
}
enum OP_TYPE {
    STATUS = 0,
    UPGRADE,
    RECOVERY,
    DELETE,
    INVALID
}
ToolAdapter <|-- ComptaskUpgradeAdapter
ToolDispatch <-- ToolAdapter
ComptaskUpgradeAdapter <- TaskUpgrade
OP_TYPE -> ComptaskUpgradeAdapter
@enduml
```
<br>

任务升级运行视图
```plantuml
@startuml
activate ToolDispatch
ToolDispatch-> ToolDispatch : 注册ComptaskUpgradeAdapter
ToolDispatch -> ComptaskUpgradeAdapter :  Init
activate ComptaskUpgradeAdapter
ComptaskUpgradeAdapter -> PUCtrl : CheckAllOffline
ComptaskUpgradeAdapter -> ZKAdapoter: SetLock
ToolDispatch -> ComptaskUpgradeAdapter :  Excu
ComptaskUpgradeAdapter -> ComptaskUpgradeAdapter : checkOptition
ComptaskUpgradeAdapter -> TaskUpgrade : Excute
activate TaskUpgrade
alt UPGRADE
TaskUpgrade -> TaskUpgrade:UpdateTaskFromOld
else DELETE
TaskUpgrade -> TaskUpgrade:DeleteOldTask
end
TaskUpgrade -> ComptaskUpgradeAdapter: exit
deactivate TaskUpgrade
ComptaskUpgradeAdapter -> ZKAdapoter: ReleaseLock
ComptaskUpgradeAdapter -> ToolDispatch : exit
ToolDispatch -> ComptaskUpgradeAdapter: release
@enduml
```
<br>

compaction_file_helper二级模块
```plantuml
@startuml
skinparam classAttributeIconSize 0
class TaskUpgrade {
	-CompManagerFileHelper* managerfile_helper_
    -CompMainTaskFileHelper* maintaskfile_helper_
    -CompMainTaskFileHelperV1* maintaskfile_v1_helper_
    -UpgradeMarkFileHelper* upgrade_markfile_helper
    +void UpdateTaskFromOld()
    +void DeleteOldTask()
    -void SetLock()
    -void ReleaseLock()
}
class CompMainTaskFileHelperV1 {
	-hdfsa::IHdfsAccessService* hdfs_
	CompactTaskState GetTaskStateFromFileName()
	bool GetMainTaskInfo()
	bool GetAllMainTaskFromScheduler()
	void ClearAllTaskV1File()
}
class CompMainTaskFileHelper {
	-hdfsa::IHdfsAccessService* hdfs_
	bool CreateMainTask()
	bool DeleteMaintask()

}
class CompManagerFileHelper {
	-hdfsa::IHdfsAccessService* hdfs_
	bool CreateMaintaskMgr()
	bool DeleteMaintaskMgr()
}
Class CompactMainTaskInfoV1 {
void UpgradeMainTaskInfo()
}
Class CompactMainTaskInfoV2 {

}
Class UpgradeMarkFileHelper {
	-hdfsa::IHdfsAccessService* hdfs_
	void MarkUpgradingFile()
	void MarkUpgradedFile()
	bool IfUpgraded()
	void UnMarkUpgradeFile()
	void MarkAllFileUpgrade()
	void ClearAllFileUpgradeMark()
}
  
TaskUpgrade .> CompMainTaskFileHelper
TaskUpgrade ..> CompManagerFileHelper
UpgradeMarkFileHelper <. TaskUpgrade
CompMainTaskFileHelperV1 <.. TaskUpgrade
CompMainTaskFileHelperV1 .> CompactMainTaskInfoV1
CompMainTaskFileHelper .> CompactMainTaskInfoV2
CompManagerFileHelper .> CompactMainTaskInfoV2
CompactMainTaskInfoV1 ..> CompactMainTaskInfoV2
@enduml
```
<br>

任务升级运行视图--文件操作
```plantuml
@startuml
activate TaskUpgrade
alt UPGRADE
	TaskUpgrade -> TaskUpgrade: UpdateTaskFromOld
	activate TaskUpgrade
	TaskUpgrade -> CompMainTaskFileHelperV1 : GetAllMainTaskFromScheduler
	CompMainTaskFileHelperV1 -> TaskUpgrade : all maintask filelist
	loop filelist
		TaskUpgrade -> UpgradeMarkFileHelper : IfUpgraded
		UpgradeMarkFileHelper -> TaskUpgrade : result
		alt Unupgrade
			TaskUpgrade->CompMainTaskFileHelperV1 : GetMainTaskInfo
			TaskUpgrade<-CompMainTaskFileHelperV1 : task info
			activate TaskUpgrade
			TaskUpgrade -> CompactMainTaskInfoV1 : UpgradeMainTaskInfo
			deactivate TaskUpgrade
			TaskUpgrade -> CompMainTaskFileHelper : CreateMainTask
			alt Init Running
				TaskUpgrade -> CompManagerFileHelper : CreateMaintaskMgr
			end
		else Upgrade	
		end
	end
	deactivate TaskUpgrade
else DELETE
	TaskUpgrade -> TaskUpgrade: DeleteOldTask
	activate TaskUpgrade
	TaskUpgrade -> CompMainTaskFileHelperV1 : DeleteAllTask
	TaskUpgrade -> UpgradeMarkFileHelper : ClearAllFileUpgradeMark
end
@enduml
```


<br>

任务升级运行视图--公共数据类型
```plantuml
@startuml
object CompactTaskId {
	std::string：query_id_
	int：sequence_no_
}
object CompactTaskIdV1 {
    std::string m_receive_pu
    int m_sequence_no
    uint64_t m_receive_ts
}
object ResultInfo {
    uint m_successCount
    uint m_failedCount
}
object RepeatInfo {
    int m_repeatCount
    int m_repeatInterval
}
object CompactOptimization {
    std::string db_name_
    std::string pc_name_
}
object TaskMemo {
    int64_t compact_filesize_threshold
    int compact_group_num
}
object CompactTaskInfoDataV1 {
    CompactTaskIdV1 _task_id
    CompactTaskState _state
    bool _repeat_flag
    bool _sub_task_flag
    RepeatInfo _repeat_info
    ResultInfo _result_info
    std::string _db_name
    std::string _schema_name
    std::string _table_name
    std::string _partition_name
}
object CompactTaskInfoDataV2 {
    CompactTaskId task_id
    std::string receive_pu
    CompactTaskState state
    CompactOptimization optimizat
    bool repeat_flag
    bool sub_task_flag
    bool sync_task_flag
    RepeatInfo repeat_info
    ResultInfo result_info
    std::string db_name
    std::string schema_name
    std::string table_name
    std::string partition_name
    std::string pc_name
    std::string executenode
    TaskMemo memo
}
CompactTaskInfoDataV1 -> CompactTaskIdV1
CompactTaskInfoDataV1 --> ResultInfo
CompactTaskInfoDataV1 --> RepeatInfo
CompactTaskId <-- CompactTaskInfoDataV2
ResultInfo <-- CompactTaskInfoDataV2
RepeatInfo <-- CompactTaskInfoDataV2
CompactTaskInfoDataV2 -> CompactOptimization
TaskMemo <- CompactTaskInfoDataV2 
@enduml

```