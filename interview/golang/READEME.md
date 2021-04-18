# golang

## golang协程和java线程的区别

- 内存区域不同
  - golang协程运行在native stack上
  - java线程运行在java stack（native heap）上
- 调度不同
  - golang协程调度基于MPG模型。使用time.Sleep或socket产生io阻塞时，对应的goroutine会被挂起，线程就可以去调度其他goroutine了。 
  - java线程调度基于操作系统对线程的调度。对标golang，java中相同的概念是reactor pattern，对应的是nio + thread/netty。
- 线程同步/内存模型略有不同
  - golang
    - channel
    - 锁和信号量
    - waitgroup
    - atomic
    - select
  - java
    - 锁和信号量
    - join
    - atomic
