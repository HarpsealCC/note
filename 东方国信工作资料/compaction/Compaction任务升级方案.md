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
        :添加任务锁，只允许一个节点进行任务升级;
        repeat:进行升级 
            if (该任务是否升级完毕?) then (yes)
            else (no)
                :读取旧任务信息;
                :在新文件目录下创建对应的任务文件;
                :将旧的任务文件标志为已经升级过了;
            endif
            backward:下一个任务文件;
        repeat while (是否是最后一个文件?)is(no) not(yes)
    :全部任务升级完成;
    :解除任务锁，任务升级结束;
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