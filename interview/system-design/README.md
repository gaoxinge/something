# system design

## 微服务容错

- 雪崩
- 降级
- 熔断
- 限流
- 隔离
- 超时

### 参考

- [面试官：说说降级、熔断、限流](https://juejin.cn/post/6844903838231576589)
- [架构之高并发：降级和熔断](https://www.pdai.tech/md/arch/arch-y-reduce.html)
- [微服务容错 - 隔离熔断限流](https://segmentfault.com/a/1190000020791119)
- [服务雪崩、熔断、降级和限流](https://github.com/chenqingyun/all-in-java/blob/master/note/%E5%88%86%E5%B8%83%E5%BC%8F%E6%9C%8D%E5%8A%A1%E6%A1%86%E6%9E%B6%E5%92%8C%E4%B8%AD%E9%97%B4%E4%BB%B6/%E6%9C%8D%E5%8A%A1%E9%9B%AA%E5%B4%A9%E3%80%81%E7%86%94%E6%96%AD%E3%80%81%E9%99%8D%E7%BA%A7%E5%92%8C%E9%99%90%E6%B5%81.md)

### 框架

- [Netflix/Hystrix](https://github.com/Netflix/Hystrix)
- [alibaba/Sentinel](https://github.com/alibaba/Sentinel)
- [alibaba/sentinel-golang](https://github.com/alibaba/sentinel-golang)

## 分布式ID

分布式ID主要是为了保证后端有状态服务即使经过多次重试也能达到exact once的效果

### 场景

- 支付：后端使用分布式ID防止重复支付

### 方法

- uuid
- snowflake
- database
- redis
- zookeeper/etcd/consul

## 分布式锁

### 参考

- [How to do distributed locking](https://martin.kleppmann.com/2016/02/08/how-to-do-distributed-locking.html)

## 分布式事务

### 消息队列

- [消息队列漫谈：如何使用消息队列实现分布式事务？](https://zhuanlan.zhihu.com/p/101974130)

#### rocketmq

##### 参考

- [事务消息](https://help.aliyun.com/document_detail/43348.html)
- [RocketMQ事务消息](https://www.jianshu.com/p/84d830bee587)
- [基于RocketMQ分布式事务 - 完整示例](https://zhuanlan.zhihu.com/p/115553176)

#### kafka

- 通过produceId实现幂等性。at least once + 幂等性 = exact once
- 通过transactionId/事务控制消息/事务协调中心实现2PC，实现分布式事务

##### 参考

- [Kafka事务到底是什么意思？](https://www.zhihu.com/question/311885878)
- [Kafka 笔记 02: 事务](https://zhuanlan.zhihu.com/p/120796378)

### 刚性事务（ACID）

#### 2PC/3PC/XA

- 事务发起服务从事务管理器获取全局事务ID
- 事务发起服务使用全局事务ID向各服务发送请求
- 事务发起服务使用全局事务ID向事务管理器发送PREPARE消息
- 事务管理器转发PREPARE消息给各服务，然后接受各服务的响应
- 如果全部响应OK，事务管理器发送COMMIT消息给各服务；否则，发送ROLLBACK消息给各服务
- 事务发起服务接受事务管理器的响应

### 柔性事务（BASE）

#### TCC

- 各服务提供Try，Confirm，Cancel接口，其中Confirm和Cancel都是幂等的
- 事务发起服务向事务管理器发送Try消息，请求各服务的Try接口，然后接受各服务的响应
- 如果全部响应OK，事务发起服务请求各服务的Confirm接口；否则，请求Cancel接口
- 事务发起服务接受事务管理器的响应

#### saga

- 按照T1，T2，...，Tn的顺序执行事务
- 如果失败，按照Cn，...，C2，C1的顺序补偿

#### 本地消息表

- 条件性事务服务在同一事务中写入业务表和本地消息表
- 条件性事务服务把消息投递到消息队列里
  - 如果成功，则结束
  - 否则，反查消息队列中消息的状态
    - 如果成攻，则结束
    - 否则，根据消息表，继续把消息投递到消息队列里
- 非条件性事务服务消费消息

#### 消息队列

- rocketmq封装复用了上述步骤

#### 最大努力通知

- 减少上述步骤的重试，降低了一致性

### 参考

- [分布式事务，这一篇就够了](https://xiaomi-info.github.io/2020/01/02/distributed-transaction/)
- [微服务中的分布式事务方案](https://jeremyxu2010.github.io/2020/03/%E5%BE%AE%E6%9C%8D%E5%8A%A1%E4%B8%AD%E7%9A%84%E5%88%86%E5%B8%83%E5%BC%8F%E4%BA%8B%E5%8A%A1%E6%96%B9%E6%A1%88/)
- [分布式事务的实现原理](https://draveness.me/distributed-transaction-principle/)
- [支付宝运营架构中柔性事务指的是什么？](https://www.zhihu.com/question/31813039)
- [常用的分布式事务解决方案有哪些?](https://www.zhihu.com/question/64921387)
- [再有人问你【分布式事务】，把这篇扔给他](https://zhuanlan.zhihu.com/p/41891052)
- [基于本地消息表的分布式事务解决方案总结](https://zhuanlan.zhihu.com/p/147817106)

### 框架

- [seata/seata](https://github.com/seata/seata)
- [opentrx/seata-golang](https://github.com/opentrx/seata-golang)

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

### 特性

- 缓存穿透：多个key没有在redis中找到数据，大量的请求直接打到mysql上
  - 预热
  - 提前过滤不存在或者不合理的key
  - 限流
- 缓存击穿：某个key在redis中过期后，大量的请求直接打到mysql上
  - 分布式锁
  - key不过期，异步更新
  - 限流
- 缓存崩溃：多个key在redis中过期后，大量的请求直接打到mysql上
  - 随机过期时间
  - 分布式锁
  - key不过期，异步更新
  - 限流

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
