## 模型

```
+--------+                  +-------+                    +--------+
|        | server bandwidth |       |  client bandwidth  |        |
| server | ---------------- | route | ------------------ | client |
|        |                  |       |                    |        |
+--------+                  +-------+                    +--------+ 
```

## 客户端带宽

比如电信带宽100M，实际指100Mbps。不考虑上下行的话，换算成对应的网速为100Mbps * 1000 = 100000Kbps，100000Kbps / 8 = 12500KB/s，12500KB/s / 1024 = 12MB/s。另外，这个带宽的利用率大概为70%，因此实际的网速为12MB/s * 0.7 = 8MB/s。

## 服务端带宽

### 设置

- 数值
- 独享/共享

### 估计

网站大小50KB，打开一个网站需要在8秒内完成。如果预计用户在1000人时，所需带宽为1000 * 50 / 8 = 6250KB/s，6250 * 8 / 1000 = 50Mbps，即50M的带宽。

## 参考文献

- [什么是带宽，举个例子说一下，整天说的服务器带宽有限，是什么意思？](https://blog.csdn.net/ideality_hunter/article/details/77923335)
- [服务器带宽](https://blog.csdn.net/zz770750140/article/details/78170539)
- [服务器网站5m带宽在线多少人?](https://blog.csdn.net/yrx1004/article/details/80228793)
- [云服务器多大带宽合适](http://www.yiqnet.com/news/n875.html)
- [网络服务器带宽Mbps、Mb/s、MB/s的区别](https://jingyan.baidu.com/article/0964eca23e86cc8285f53685.html)
- [上行带宽和下行带宽是什么意思？](https://www.192ly.com/basic/upstream-bandwidth-and-downstream-bandwidth.html)
- [带宽与网速，有什么区别 ](https://zhidao.baidu.com/question/419540077.html)
- [什么是Mbps、Kbps、bps、kb、mb及其换算和区别](https://blog.csdn.net/u010178308/article/details/78328630)
