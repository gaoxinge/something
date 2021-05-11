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
