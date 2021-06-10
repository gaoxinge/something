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

## 参考

- [再过半小时，你就能明白kafka的工作原理了](https://zhuanlan.zhihu.com/p/68052232)