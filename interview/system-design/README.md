# system design

## 缓存

在大量数据读取的场景下，在web和mysql之间加入一层redis作为缓存，主要是为了优化web读取数据的性能，具体如下：

- 降低mysql的负载
- 降低web读取数据的延时

在设计方案时，需要考虑：

- 实现难度
- 写入数据的延时
- redis和mysql的数据一致性
  - redis和mysql写入顺序不一致
  - redis中数据过期
  - redis或者mysql写入崩溃或故障

### 方案1：读写分离/读时更新

#### 架构

```
     |----> redis
web -|
     |----> mysql
```

- 写：web直接把数据写入mysql
- 读：如果redis里面有数据，那么web直接从redis里面读取；如果redis里面没有数据，那么web从数据库里面读取，并在redis里面写入，同时设置对应的ttl过期时间

#### 优缺点

- 优点：实现简单；不影响写入数据的延时
- 缺点：redis中数据过期导致一致性问题（取决于ttl的长短）

### 方案2：多写/写时更新

#### 架构

```
     |----> redis
web -|
     |----> mysql
```

- 写：web把数据写入mysql，并更新redis中的数据。由于需要考虑redis或者mysql写入崩溃或者故障导致的一致性问题，因此需要在redis中设置对应的ttl过期时间
- 读：由于需要考虑redis或者mysql写入崩溃或者故障导致的一致性问题，因此web不能直接从redis读取数据，需要和方案1中的读取方式保持一致

#### 优缺点

- 优点：实现简单；数据更新及时
- 缺点：增加写入数据的延时；会引入redis和mysql写入顺序不一致

### 方案3：消息队列1/多写

#### 架构

```
     |----> kafka ----> redis
web -|
     |----> mysql
```

- 写：web把数据写入mysql，并写入kafka，异步更新redis
- 读：如果redis里面有数据，那么web直接从redis里面读取；如果redis里面没有数据，那么web从数据库里面读取，并在redis里面写入

#### 优缺点

- 优点：不影响写入数据的延时
- 缺点：实现复杂；会引入redis和mysql写入顺序不一致

### 方案4：消息队列2/CDC

#### 架构

```
web ----> mysql ----> kafka ----> redis
```

- 写：web把数据写入mysql，并通过binlog，异步更新redis
- 读：如果redis里面有数据，那么web直接从redis里面读取；如果redis里面没有数据，那么web从数据库里面读取，并在redis里面写入

#### 优缺点

- 优点：不影响写入延时；一致性比较好
- 缺点：实现复杂

### 方案5：消息队列3/stream

#### 架构

```
                 |----> redis
web ----> kafka -|
                 |----> mysql
```

- 写：web把数据写入kafka，同步更新mysql，异步更新redis
- 读：如果redis里面有数据，那么web直接从redis里面读取；如果redis里面没有数据，那么web从数据库里面读取，并在redis里面写入

#### 优缺点

- 优点：一致性比较好
- 缺点：实现复杂；增加写入延时

## 秒杀系统

秒杀系统的关键是通过系统架构设计，使得从前端，后端到数据库流量逐级减少，防止大量的流量直接打到数据库上。同时需要考虑

- 防止超卖
- 防止提前秒杀
- 尽量公平
- 尽量保持原有系统架构，添加秒杀功能

### 架构

```
                          ---------> redis
                          |
前端 ---> nginx ---> web server ---> database 
```

### 前端

- 防止提前秒杀：下单按钮置灰，并且下单url延迟到秒杀时刻暴露。如果做不到，使用动态url，并对url加盐。如果还是做不到，使用后端判断商品是否存在，或者判断商品是否在秒杀活动中
- 反爬虫：防止同一个用户使用脚本在短时间内进行多次请求
- 同步/异步：使用同步交互，还是异步交互。如果是异步交互，需要增加消息队列作作为消息中间件
- 前端限流

### nginx

- 负载均衡

### web server

- 限流
- redis：预先判断商品库存是否足够
- database：
  - 悲观锁/乐观锁
  - 分布式事务

### redis

- 限流
- 存放商品库存

### database

- 商品表，活动表（秒杀），库存表，订单表，支付表

### 参考

- [如何设计秒杀系统？](https://www.zhihu.com/question/54895548)

## top k/heavy hitter

某些场景需要近乎实时的统计：在某个时间区间内，某些链接被点击的次数中排名的靠前的几个或者最多的那个。这类问题需要下面的概念：

- 流式计算
- 数据分区
- 滑动窗口

### 方案1

```
web server 1 ---|              |---> top-k reducer ---|
                |              |                      |
web server 2 ---|---> kafka ---|---> top-k reducer ---|---> top-k merger ---> mysql
                |              |                      |
web server 3 ---|              |---> top-k reducer ---|
```

- 写
  - web server把数据写入kafka（同时写入滑动窗口的标记）
  - kafka根据链接作partition，把点击分发给top-k reducer
  - top-k reducer把滑动窗口内的top k个链接统计完后，发给top-k merger汇总
  - top-k merger统计完滑动窗口内的top k个链接后，写入数据库
- 读
  - 数据库字段：top-k，start\_time（索引），end\_time（start\_time + interval0）
  - 给定start\_time0，end\_time0（start\_time + interval0），从数据库里面读取start\_time介于\[start\_time0, end\_time0)中，start\_time最小的top-k
- 问题
  - 滑动窗口标记
  - 动态partition
  - 容错，高可用，exact once
  - 链接去重

### 方案2

- spark
- flink

### 参考

- [Top K Frequent Items Algorithm](https://zpjiang.me/2017/11/13/top-k-elementes-system-design/)
- [System Design Interview - Top K Problem (Heavy Hitters)](https://serhatgiydiren.github.io/system-design-interview-top-k-problem-heavy-hitters)
- [System Design Interview: Distributed Top K Frequent Elements in Stream](https://levelup.gitconnected.com/system-design-interview-distributed-top-k-frequent-elements-in-stream-2e92d63d777e)
- [深度解析某头条的一道面试题](https://zhuanlan.zhihu.com/p/35143913)
- [Efficient Computation of Frequent and Top-k Elements in Data Streams](https://www.cs.ucsb.edu/sites/cs.ucsb.edu/files/docs/reports/2005-23.pdf)
- [An Optimal Strategy for Monitoring Top-k Queries in Streaming Windows](http://davis.wpi.edu/xmdv/docs/EDBT11-diyang.pdf)
- [Distributed Top-K Monitoring](http://infolab.stanford.edu/~olston/publications/topk.pdf)
