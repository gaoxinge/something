# architecture

- [x] [crossoverJie](https://github.com/crossoverJie)
- [x] [CyC2018](https://github.com/CyC2018)
- [x] [Unified Modeling Language](https://en.wikipedia.org/wiki/Unified_Modeling_Language)
- [x] [我所理解的OOP——UML六种关系](http://www.cnblogs.com/dolphinX/p/3296681.html)
- [x] [Design Patterns](https://book.douban.com/subject/1436745/)
- [x] [如何正确地使用设计模式？](https://www.zhihu.com/question/23757906/answer/25567356)
- [x] [SOLID](https://en.wikipedia.org/wiki/SOLID)
- [x] [阿里巴巴Java开发手册](https://book.douban.com/subject/27605355/)
- [x] [Clean Code](https://book.douban.com/subject/3032825/)
- [x] [Clean Architecture](https://book.douban.com/subject/26915970/)
- [x] [大型分布式网站架构](http://www.cnblogs.com/itfly8/category/756114.html)
- [x] [大型网站技术架构](https://book.douban.com/subject/25723064/)
- [x]  [Microservices in Practice](https://medium.com/microservices-in-practice)

## UML

UML, Unified Modeling Language, is used for modeling, which is not only for OOP language, like Java.

### OOP, Java

- Inheritance：继承
- Implementation：实现
- Dependency：依赖
- Association：关联
- Aggregation：聚合
- Combination：组合

## design pattern

![1](https://github.com/gaoxinge/something/blob/master/architecture/1.png)

## solid

- Single Responsibility Principle：单一责任原则
- Open Closed Principle：开放封闭原则
- Liskov Substitution Principle：里氏替换原则
- Interface Segregation Principle：接口分离原则
- Dependency Inversion Principle：依赖倒置原则

## clean code

### error handling

#### unchecked exception

- [Java异常：选择Checked Exception还是Unchecked Exception?](https://blog.csdn.net/kingzone_2008/article/details/8535287)

#### null

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        List<Integer> a;
        System.out.println(a);     // compile error: uninitialize
        
        List<Integer> b = null;
        System.out.println(b);     // null
        
        List<Integer> c = new ArrayList<>();
        System.out.println(c);     // []
    }
}
```

## 大型网站技术架构

### 流程

- 横向切分

```
---------------
|   layer1    |
---------------
|   layer2    |
---------------
|   layer3    |
---------------
```

- 纵向切分

```
----------------
| a1 | a2 | a3 |
----------------
| b1 | b2 | b3 |
----------------
| c1 | c2 | c3 |
----------------
```

- 按照业务切分：注重可扩展性
- 按照模块部署：注重可伸缩性

### 秒杀系统

#### 页面

- 秒杀准备页面
- 秒杀进行页面
- 订单确认页面
- 秒杀结束页面

#### 页面定时切换

- 客户端轮询
- 客户端websocket
- 服务端定时推送

#### 架构

```
client ---> web ---> service ---> db
```

#### 流程

```
client ---> load balance ---> web ---> service ---> db 
                                         |
                                         |
                                         v
                                   global count db
```

```
client ---> load balance ---> web ---> service ---> kafka ---> db
   |                                                           ^
   |                                                           |
   -------------------------------------------------------------
```

### 画大饼

- 每个公司都有自己的主要业务，而主要业务带来的价值就是主要价值。任何的业务架构是开放的，但是主要部分的落实是封闭的。所以在主要部分完成之前，业务所带来的价值可能是不确定的。
- 在一家初创公司，画大饼是正常的事情。此时你的个人价值很可能高于业务的价值，但是你的个人价值有可能小于业务的未来价值。
- 在一家大公司，画大饼是不正常的事情。