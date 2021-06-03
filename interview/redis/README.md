# redis

## 架构

## 数据类型

### 底层数据类型

- int：整数
- raw：字符串
- linkedlist：双端链表
- ziplist：压缩列表
- skiplist：跳跃表
- ht：字典
- intset：整数集合

### redisObject

- type：类型
- encoding：编码
- lru：LRU时间
- refcount：引用计数
- ptr：底层数据类型

### redis数据类型

- string：字符串
  - 编码：整数/字符串
- list：列表
  - 编码：双端链表/压缩列表
- hash：哈希表
  - 编码：压缩列表/字典
- set：集合
  - 编码：字典/整数集合
- zset：有序集合
  - 编码：跳跃表/压缩列表

## 持久化

- RDB：redis database，快照
- AOF：append only file，写日志

## 高可用

## 缓存雪崩
