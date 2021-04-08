compaction任务模块重构：
```plantuml
@startmindmap
* compaction任务模块重构介绍
** 重构的背景介绍
*** 什么是compaction
*** 行云的compaction
*** 对比其他家的compaction
*** 为什么重构
**** 原compaction的大概工作原理
**** 存在的问题
**** 重构点

** 重构的方案简介
*** 针对各个已知问题提出解决方案
*** 为新增的功能提供解决方案

** 重构后的主要功能
*** 添加任务同步、异步
*** 停止任务
*** 重分配任务
*** monitor
@endmindmap

```
程序启动时，所有节点参与leader选举
```plantuml
@startmindmap
* leader选举
-- PU1
-- PU2
-- PU3
-- PU4
++ PU5
++ PU6
++ PU7
@endmindmap
```
<br>

leader选举结束后PU1为leader，其他节点为worker
```plantuml
@startmindmap
*[#lightblue] PU1(leader)
-- PU2
-- PU3
-- PU4
++ PU5
++ PU6
++ PU7
@endmindmap
```
<br>

在PU6节点下发compaction任务，leader节点获取任务信息，生成主任务
```plantuml
@startmindmap
*[#lightblue]: PU1(leader)
获取任务信息
生成主任务;
-- PU2
-- PU3
-- PU4
++ PU5
++[#Orange] PU6 <= 添加任务
++ PU7
@endmindmap
```
<br>

leader节点根据table下的分区个数，创建子任务，分配到各个worker节点
```plantuml
@startmindmap
*[#lightblue]:                       创建子任务
分配任务 <= PU1(leader) => 分配任务;
--[#lightgreen] PU2 <= 子任务1
-- PU3
--[#lightgreen] PU4 <= 子任务2
++[#lightgreen] 子任务3 => PU5
++ PU6
++ PU7
@endmindmap
```
<br>

各个worker节点处理任务，leader监控子任务执行情况并更新主任务信息
```plantuml
@startmindmap
*[#lightblue]:PU1(leader)
收集子任务状态
更新主任务信息;
--[#lightgreen] PU2 ： 处理子任务1
-- PU3
--[#lightgreen] PU4 ： 处理子任务2
++[#green] PU5 ： 子任务3处理完成
++ PU6
++ PU7
@endmindmap
```
<br>

leader检测所有子任务都完成后，leader节点修改主任务状态为完成并删除子任务
```plantuml
@startmindmap
*[#lightblue]:PU1(leader)
子任务全部完成
修改主任务信息
删除子任务;
--[#green] PU2 ： <s>子任务1处理完成</s> 
-- PU3
--[#green] PU4 ： <s>子任务2处理完成</s>
++[#green] PU5 ： <s>子任务3处理完成</s>
++ PU6
++ PU7
@endmindmap
```
<br>

如果在任务执行过程中有节点离线，就由leader对这个节点下的任务进行重分配（一致性hash）
```plantuml
@startmindmap
*[#lightblue]:PU1(leader)
感知到PU2离线
将子任务1分配到PU3;
--[#red] <s>PU2 ： 处理子任务1</s>
--[#lightgreen] PU3 :  处理子任务1
--[#lightgreen] PU4 ： 处理子任务2
++[#lightgreen] PU5 ： 处理子任务3
++ PU6
++ PU7
@endmindmap
```
<br>

如果leader节点出问题了，则其他节点需要进行leader选举，选举期间不需要暂停子任务处理
```plantuml
@startmindmap
*[#red] <s>PU1(leader) 离线</s>
-- PU2 (leader选举)
--[#lightgreen] PU3 :  处理子任务1 (leader选举)
--[#lightgreen] PU4 ： 处理子任务2 (leader选举)
++[#lightgreen] PU5 ： 处理子任务3 (leader选举)
++ PU6 (leader选举)
++ PU7 (leader选举)
@endmindmap
```
<br>

leader选举结束后，由新的leader行使职能
```plantuml
@startmindmap
*[#lightblue] PU2(leader)
--[#red] <s>PU1 : 离线</s>
--[#lightgreen] PU3 :  处理子任务1
--[#lightgreen] PU4 ： 处理子任务2
++[#lightgreen] PU5 ： 处理子任务3
++ PU6
++ PU7
@endmindmap
```
<br>

```plantuml
@startsalt
{
{T
 + cluster.compact
 ++ Compaction
 +++ Scheduler
 ++++ Main Task Info 1
 ++++ Main Task Info 2
 ++++ ......
 +++ TaskAssigned
 ++++ PUID1_InterPort
 +++++ SubtaskID1
 ++++++ TaskState
 ++++++ TaskInfo File
 +++++ SubtaskID2
 ++++++ TaskState
 ++++++ TaskInfo File
 +++++ ......
 ++++ PUID2_InterPort
 +++++ SubtaskID3
 +++++ ......
}
}
@endsalt
```
<br>

```plantuml
@startsalt
{+
{* File | Edit | Source | Refactor
 Refactor | New | Open File | - | Close | Close All }
{/ General | Fullscreen | Behavior | Saving }
{
{ Open image in: | ^Smart Mode^ }
[X] Smooth images when zoomed
[X] Confirm image deletion
[ ] Show hidden images
}
[Close]
}
@endsalt
```
<br>

集群启动时进行leader（monitor）选举
（依托job_scheduler模块）
```plantuml
@startmindmap
* leader（monitor）选举
-- PU1
-- PU2
-- PU3
-- PU4
++ PU5
++ PU6
++ PU7
@endmindmap
```
<br>

选举出的monitor节点定时执行维护历史信息与离线节点任务重分配的功能
```plantuml
@startmindmap
*[#lightblue]: PU1 (moniter) 定时执行
负责历史信息的定时压缩与删除
负责离线节点的任务重分配;
-- PU2
-- PU3
-- PU4
++ PU5
++ PU6
++ PU7
@endmindmap
```
<br>

向PU6添加任务，则PU6成为该任务的manager，负责子任务的分配
子任务执行结果收集，与主任务状态的维护
```plantuml
@startmindmap
*[#lightblue] PU1(monitor)
-- PU2
-- PU3
-- PU4
++ PU5
++[#Orange] (Manager)PU6 <= 添加任务
++ PU7
@endmindmap
```
<br>


```plantuml
@startmindmap
*[#Orange]  分配子任务 <= (Manager)PU6 => 分配子任务
++[#lightblue] PU1(monitor)
-- PU2
--[#lightgreen] PU3（子任务1）
--[#lightgreen] PU4（子任务2）
++[#lightgreen] PU5（子任务3）
++ PU7
@endmindmap
```
<br>

```plantuml
@startmindmap
*[#Orange]:  (Manager)PU6
子任务1完成，收集子任务执行信息
更新主任务状态，删除子任务;
++[#lightblue] PU1(monitor)
-- PU2
--[#green] PU3 <s>（子任务1完成）</s>
--[#lightgreen] PU4（子任务2）
++[#lightgreen] PU5（子任务3）
++ PU7
@endmindmap
```
<br>

```plantuml
@startmindmap
*[#Orange]: <s>(Manager)</s>PU6
所有子任务都完成后
更新主任务信息为done
之后不再担任此任务的manager;
++[#lightblue] PU1(monitor)
-- PU2
--[#green] PU3 <s>（子任务1完成）</s>
--[#green] PU4 <s>（子任务2完成）</s>
++[#green] PU5 <s>（子任务3完成）</s>
++ PU7
@endmindmap
```
<br>

```plantuml
@startmindmap
*[#Orange]: (Manager)PU6
如果是重复任务
则当所有子任务完成后
由Manager再次进行子任务分配;
++[#lightblue] PU1(monitor)
--[#lightgreen] PU2（第二次子任务2）
-- PU3
--[#lightgreen] PU4（第二次子任务3）
++ PU5
++ PU9
++[#lightgreen] PU7(第二次子任务1)
@endmindmap
```
<br>

不同的任务Manager节点可以不同，各自维护属于自己的主任务逻辑
```plantuml
@startmindmap
*[#Orange] (任务1Manager)PU6
++[#pink] PU1(monitor)(任务2子任务1)
--[#Orange] (任务2Manager)PU2 <= 任务2添加
--[#green] PU3 <s>（任务1子任务1完成）</s>
--[#lightgreen] PU4（任务1子任务2）
++[#lightgreen] PU5（任务1子任务3）
++[#Pink] PU7（任务2子任务2）
@endmindmap
```
<br>

当有节点离线时，monitor会进行监控，如果该节点下只有子任务
monitor不做处理，但所属的Manger节点在收集子任务状态时如果检测到节点离线
认为该节点执行任务失败
```plantuml
@startmindmap
*[#lightblue]: PU1(monitor)
monitor不做处理;
-- PU2 
--[#lightgreen]  PU3（子任务1）
--[#lightgreen]  PU4 (子任务2)
++[#red] <s>PU5离线 (子任务3) </s>
++[#Orange] (Manager)PU6 认为子任务3执行失败
++ PU7
@endmindmap
```
<br>

如果离线节点下存在manager任务，monitor节点会将其进行重分配
```plantuml
@startmindmap
*[#lightblue]: PU1(monitor)
每小时执行一次重分配检测
检测到PU6离线
将Manager重新分配到PU2;
--[#orange] (Manager)PU2
--[#lightgreen]  PU3（子任务1）
--[#lightgreen]  PU4 (子任务2)
++[#lightgreen]  PU5 (子任务3) 
++[#red] <s>(Manager)PU6离线</s>
++ PU7
@endmindmap
```
如果没有满足的重分配节点（基本上就是整个pc下线了这个情景），那么这个任务会被标记为cancel

<br>


```plantuml
@startsalt
{
{T
 + <color:red>cluster.compact
 ++ Compaction_v2
 +++ Scheduler
 ++++ MainTask1 Id
 +++++ TaskState
 +++++ TaskInfo File
 ++++ MainTask2 Id
 +++++ TaskState
 +++++ TaskInfo File
 ++++ ......
 ++++ Compress
 +++++ Time1 Compressfile
 +++++ Time2 Compressfile
 +++++ .......
 +++ TaskAssigned
 ++++ PUID1_InterPort
 +++++ SubtaskID1
 ++++++ TaskState
 ++++++ TaskInfo File
 +++++ SubtaskID2
 ++++++ TaskState
 ++++++ TaskInfo File
 +++++ ......
 ++++ PUID2_InterPort
 +++++ SubtaskID3
 +++++ ......
}
}
@endsalt
```
<br>

```plantuml
@startyaml
CompactTaskId: "taskid"
CompactTaskState: "state"
bool: repeat_flag
bool: sub_task_flag
RepeatInfo: 
	int: repeatCount
	int: repeatInterval
ResulttInfo:
	int: successCount
	int: failedCount
string: db_name
string: schema_name
string: table_name
string: partition_name
@endyaml
```
<br>

