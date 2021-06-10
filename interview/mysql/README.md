# mysql

## 架构

- client
- server
- storage

## storage

- innodb: B+树
- myisam

## storage engine

### 考虑

- 读
  - 键查询
  - 小范围查询（磁盘IO）
  - 范围查询
- 写
- 空间

### 对比

- 数组/链表
  - 平均复杂度O(n)，慢
- 二叉树
  - 普通二叉树平均复杂度O(logn)，最坏复杂度O(n)，不稳定
  - 平衡二叉树最坏复杂度O(logn)，但对磁盘IO不友好
- 哈希表
  - 平均复杂度O(1)，不稳定
- 跳表
  - 平均复杂度O(logn)，不稳定
- B树
  - 从根节点开始，高度保持固定，每层有多个节点，每个节点有多个键/索引
  - 数据/记录存放在内部节点和叶子节点上
  - 稳定的键查询，对磁盘IO友好，不支持范围查询
- B+树
  - 从根节点开始，高度保持固定，每层有多个节点，每个节点有多个键/索引
  - 键/索引存放在内部节点上，数据/记录存放在叶子节点上，而且每层节点使用双向链表连接
  - 稳定的键查询，对磁盘IO友好，支持范围查询
- LSM
  - 读放大：compaction，bloomfilter
  - 空间放大：compaction

## index

- 主键/聚簇索引
  - 键：主键，值：记录
- 二级索引
  - 键：索引，值：主键
  - 回表
- 联合索引
  - 键：联合索引（顺序），值：主键
  - 回表

#### 索引失效，explain

- [【MySQL】索引失效以及explain应对](https://blog.csdn.net/tr1912/article/details/81319574)
- [一张图搞懂MySQL的索引失效](https://segmentfault.com/a/1190000021464570)

## log

### transaction

- start：<START T>
- commit：<COMMIT T>

### undo/redo

- undo：回滚日志，记录旧值，<T, A, x>
- redo：重做日志，记录新值，<T, A, x>
- undo/redo：<T, A, x1, x2>

### wal/steal/force

- wal：<T, A, x>需要先于脏数据落盘
- steal：<COMMIT, T>不需要先于脏数据落盘
- no steal：<COMMIT, T>需要先于脏数据落盘，蕴含wal
- force：<COMMIT, T>需要后于脏数据落盘
- no force：<COMMIT, T>不需要后于脏数据落盘

### crasy recovery

#### undo

- 原则
  - wal：<T, A, x>需要先于脏数据落盘
  - force：<COMMIT, T>需要后于脏数据落盘
- 恢复
  - 已提交：根据force原则，已经落盘
  - 未提交：根据wal原则，回滚落盘的数据
- 结论
  - steal
  - force

#### redo

- 原则
  - no steal：<COMMIT, T>需要先于脏数据落盘
- 恢复
  - 已提交：根据no steal原则，重做未落盘的数据
  - 未提交：根据no steal原则，未落盘
- 结论
  - no steal
  - no force

#### undo/redo

- 原则
  - wal：<T, A, x1, x2>需要先于脏数据落盘
- 恢复
  - 已提交：根据wal原则，重做未落盘的数据
  - 未提交：根据wal原则，回滚落盘的数据
- 结论
  - steal
  - no force

### 分类

- 等价性
  - undo <-> force
  - redo <-> no steal
- 分类
  - steal/force：undo
  - no steal/no force：redo
  - steal/no force：undo/redo
  - no steal/force：不存在

### binlog

- 用于主从同步
- 位于server层
- 格式
  - statement，基于SQL
  - row，基于记录
  - mixed

## transaction

- A：原子性
- C：一致性
- I：隔离性
- D：持久性

## 原子性

- log

## 一致性

- 一致性指数据库的数据无论何时都能保证某种逻辑的自洽
- 一致性主要通过下面的方式保证：
  - 事务的另外三个性质
  - 显示约束：数据库的约束功能
  - 隐式约束：业务代码

## 隔离性

### 问题

- 脏读：读取到其他事务未提交的数据
- 不可重复读：读取到其他事务提交的数据。准确的说，连续读取同一条记录，但值不同
- 幻读：读取到其他事务新增的数据。准确的说，连续读取同一张表，但记录个数不同
- 更新丢失：由于隔离性，两个事务在无法相互可见的情况下，并发的修改同一条记录

### 隔离级别

- 读未提交：脏读
- 读提交：解决脏读
- 可重复读：解读不可重复读和更新丢失
- 串行化：解决幻读

### MVCC（多版本并发控制）

- 使用一致性视图/快照执行事务：每个事务都有一个唯一递增的ID，并在新增和更新数据的时候，给数据增加一个版本号，使用事务ID标记
- 一致性视图/快照遵循如下原则：
  - 自身的事务可见
  - 未提交的事务不可见
  - 创建一致性视图/快照之前的提交的事务可见
  - 创建一致性视图/快照之后的提交的事务不可见

### 锁

- 读写锁
- 行锁
- 间隙锁
- 表锁

### 读未提交

- log

### 读提交

- MVCC：事务中每个SQL语句执行结束后，都会创建一个一致性视图/快照

### 可重复读

- MVCC：事务在开始时，创建一个一致性视图/快照
- 锁：小粒度

### 串行化

- 锁：大粒度

### 参考

- [什么是脏读、不可重复读、幻读？](https://www.zhihu.com/question/458275373/answer/1873975439)
- [我以为我对Mysql事务很熟，直到我遇到了阿里面试官](https://zhuanlan.zhihu.com/p/148035779)

## 持久性

- log