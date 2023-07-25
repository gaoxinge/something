# kafka

## 作用

- 解耦
- 异步
- 削峰

## 架构

### 逻辑

```
              topic           consumer group

producer ---> partition0 ---> consumer0
   |
   |--------> partition1 ---> consumer1
   |
   |--------> partition2 ---> cunsumer2
```

### 物理

```     

               broker0                     broker1                          consumer group

producer --->  topic-partition0 (leader)   topic-partition0 (follower) ---> consumer0
   |
   |-------->  topic-partition1 (follower) topic-partition1 (leader)   ---> consumer1
```

### 描述

- topic有多个partition，每个partition被consumer group中不同的conumser消费，用于提高吞吐
- partition在多个broker上有副本，使用zookeeper选主
- producer根据zookeeper中的元信息，获取leader的位置，直接和leader通信，leader在把数据复制到follower

### 参考

- [再过半小时，你就能明白kafka的工作原理了](https://zhuanlan.zhihu.com/p/68052232)

## 分配: topic中的partition如何分配给consumer group中的consumer

### 策略

- range
- round roubin
- sticky

### rebalance

- topic: partition增加或者减少
- consumer group: consumer加入或者退出

### 参考

- [Kafka分区分配策略（Partition Assignment Strategy）](https://cloud.tencent.com/developer/article/1708388)
- [Kafka（三）：消费者消费方式、三种分区分配策略、offset维护](https://segmentfault.com/a/1190000038712658)
- [Kafka消费者组三种分区分配策略roundrobin，range，StickyAssignor](https://zhuanlan.zhihu.com/p/377209008)

## consumer

### 流程

- push vs poll: 使用poll，便于控制消费速度
- commit: 提交，更新partition上日志的offset

### 重复消费

#### 原因

- 为了消息不丢失，或者其他原因，导致producer发送重复消息
- consumer没有及时commit，导致kafka重放消息

#### 解决办法

- 生成分布式ID
- producer把上述ID写入消息，再发送给kafka
- consumer从kafka收到消息，持久化ID
- 如果kafka重放消息，consumer可以根据持久化ID，过滤重复消息

#### 参考

- [技术干货分享 | Kafka重复消费场景及解决方案](https://zhuanlan.zhihu.com/p/112745985)
- [Kafka重复消费总结](https://www.cnblogs.com/yangyongjie/p/14675119.html)
- [一文理解Kafka重复消费的原因和解决方案](https://blog.csdn.net/y277an/article/details/118165463)
- [Kafka常见的导致重复消费原因和解决方案](https://cloud.tencent.com/developer/article/1665700)
- [Kafka保证数据不丢失的原理](http://timebusker.top/2019/06/14/(%E4%BA%94)_Kafka%E5%9C%A8%E5%AE%9E%E8%B7%B5%E4%B8%AD%E9%81%BF%E5%85%8D%E9%87%8D%E5%A4%8D%E6%B6%88%E8%B4%B9%E5%92%8C%E4%B8%A2%E5%A4%B1%E6%95%B0%E6%8D%AE/)

