# network

## 序列化

### hessian

- 类型字节|定长字节
- 类型字节|长度字节|变长字节
- 类型字节|定长字节...|结束符字节

### protobuf

- 类型字节|定长字节
- 类型字节|长度字节|变长字节

### hessian vs protobuf

- 反射 vs IDL

## 应用层

### http

#### http1.0

##### 格式

- 请求行/响应行
- 请求头/响应头
- 请求数据/响应数据

##### 特点

- 一个TCP连接承载一个HTTP的请求和响应

#### http1.1
 
##### 格式

- 请求行/响应行
- 请求头/响应头
- 请求数据/响应数据

##### 改动

- 持久连接
- 请求管道化
- 增加缓存处理
- 增加断点续传

##### 特点

- 一个TCP连接承载多个HTTP的请求和响应
- 默认非管道化：下一个HTTP请求需要等待上一个HTTP响应结束
- 提出管道化：下一个HTTP请求不需要等待上一个HTTP响应结束，但是响应顺序需要和请求顺序保持一致

#### http2

##### 格式

- 头帧
- 数据帧

##### 改动

- 二进制分帧
- 头部压缩
- 多路复用
- 服务器推送

##### 特点

- 增加了帧和流的概念
  - 帧：相当于之前的一个HTTP消息，会关联一个流的ID
  - 流：包含多个相关联的帧，会关联一个TCP连接
- 一个TCP连接会承载多个流，响应顺序不需要和请求顺序保持一致

##### 参考

- [一文读懂 HTTP/2 特性](https://zhuanlan.zhihu.com/p/26559480)
- [HTTP/2 相比 1.0 有哪些重大改进？](https://www.zhihu.com/question/34074946)
- [HTTP 2.0 和 HTTP 1.1 相比有哪些优势呢？](https://www.zhihu.com/question/306768582)

#### 请求行

##### 格式

- 方法
- URL
- HTTP版本

##### 请求方法

- GET：获取资源
- POST：增加资源
- PUT：更新资源
- DELETE：删除资源
- HEAD
- CONNECT
- OPTIONS
- TRACE

#### 响应行

#### 格式

- HTTP版本
- 状态码
- 状态描述

#### 状态码，状态描述

- 1\*\*
- 2\*\*：成功
  - 200：Ok，成功
- 3\*\*：重定向
- 4\*\*：客户端错误
  - 404：Not Found，URL错误
  - 405：Method Not Allowed，方法错误
- 5\*\*：服务端错误
  - 500：Internal Server Error，服务端内部错误
  - 501：Not Implemented，服务端功能未实现
  - 502：Bad Gateway，负载均衡请求服务报错
  - 503：Service Unavailable，服务端不可用
  - 504：Gateway Time-out，负载均衡请求服务超时
  - 505：HTTP Version not supported，HTTP版本不支持

### grpc

- 基于http2

## 传输层

### UDP vs TCP

- UDP（类似网络层）
  - 无连接
  - 不可靠
- TCP
  - 面向连接
  - 可靠

### TCP

#### 连接管理

为了上面两个特性，以及性能方面的考虑，TCP采用数据流的方式实现，即把传输数据分成多块：

- 发送方需要为每块写上编号，才能发送（seq）
- 接收方需要对接收到的每块进行ACK（ack）

具体如下：

- 三次握手：为了协商编号

```
       SYN     seq=x
client -----------------------> server
       SYN ACK seq=y   ack=x+1
client <----------------------- server
       ACK     seq=x+1 ack=y+1
client -----------------------> server
```

- 四次挥手：为了确保两边都释放资源

```
       FIN ACK seq=u   ack=v-1
client -----------------------> server
       ACK     seq=v   ack=u+1
client <----------------------- server
       FIN ACK seq=w   ack=u+1
client <----------------------- server
       ACK     seq=u+1 ack=w+1
client -----------------------> server
```

- seq和ack

```
       ACK     seq=a   ack=b
client -----------------------> server
       ACK     seq=b   ack=a+1
server <----------------------- server
```

## 服务治理

- 单体应用
- 总线架构
- 微服务
- service mesh
- serverless = faas + baas

## 浏览器里输入地址后，点击响应，发生了什么

- 浏览器：浏览器解析http响应报文，获得src标签对应的依赖链接（非href对应的超链接），并继续请求，得到响应，最后渲染并返回页面
- 客户端，服务端：客户端发送请求到服务端，经过负载均衡，服务，缓存，数据库，然后返回响应
- 应用层：发送http请求报文，获取http响应报文
- 传输层：dns解析域名，得到ip地址，然后发送tcp报文
- 网络层：路由器根据路由表转发报文
- 链路层：路由器发送icmp包，获得目的地址的mac地址，然后转发

