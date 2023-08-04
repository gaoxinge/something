# learn java

- [static](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#static)
- [final](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#final)
- [data type](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#data-type)
- [primitive type and wrapper type](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#primitive-type-and-wrapper-type)
- [toString](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#tostring)
- [wrapper type and string](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#wrapper-type-and-string)
- [pass parameter by value or by reference](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#pass-parameter-by-value-or-by-reference)
- [常量池](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#常量池)
- [String](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#String)
- [io](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#io)
- [net](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#net)
- [nio](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#nio)
- [multithread](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#multithread)
- [collection](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#collection)
- [iterable, iterator](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#iterable-iterator)
- [comparable, comparator](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#comparable-comparator)
- [garbage collection](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#garbage-collection)
- [reference](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#reference)
- [adapter pattern](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#adapter-pattern)
- [decorator pattern](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#decorator-pattern)
- [proxy pattern](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#proxy-pattern)
- [factory pattern](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#factory-pattern)
- [singleton pattern](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#singleton-pattern)
- [visitor pattern](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java#visitor-pattern)

## static

- variable: have nothing to do with class
- method: have nothing to do with class
- import: `import static java.lang.Math.sin;`

## final

- class: can not be extended
- variable: constant
- method: can not be overrided

## data type

```
                                          |---> byte, short, int, long
                                          |---> float, double
             |---> primitive data type ---|---> char
             |                            |---> boolean
data type ---|
             |                       |---> class
             |---> reference type ---|---> interface
                                     |---> array
```

## primitive type and wrapper type

### preference

- wrapper type > primitive type

### transform

```
+----------------+  wrapper +----------------+
|                |  ======> |                |
| primitive type |  autobox |  wrapper type  |
|                | <======  |                |
+----------------+          +----------------+
```

### == and equals

```java
public class Test {
    public static void main(String[] args) {
        Integer a = 12345;
        Integer b = 12345;
        int c     = 12345;
        int d     = 12345;
        System.out.println(a == b);      // false, check whether a and b refer to same object  
        System.out.println(a.equals(b)); // true, check whether a's value is same as b's
        System.out.println(c == d);      // true, check whether a's value is same as b's
        System.out.println(c.equals(d)); // error
    }
}
```

## toString

Should we explicitly use method `toString` in our program? I think it is difficult to answer the question directly. So I ask another question first:

- when we invoke a method explicitly (or implicitly)

The best practice is that we invoke a method explicitly every time. Why? Because everybody should know the api of a method, then our program will decrease the dependency of programmers' common belief. However in some situations, we can omit the explicit invocation for convenience because the common belief is enough.

Now we can turn the origin question into 

- when we should explicitly use method `toString` in our program

I think the answer is

- wrapper type: implicit
- collection: implicit/explicit
- other class: explicit

## wrapper type and string

```java
Integer a = Integer.valueOf("123"); // String  ===> Integer
String  b = a.toString();           // Integer ===> String
```

## pass parameter by value or by reference

- primitive data type: by value
- class (without setter): by value
- class (with setter): by reference
- array: by reference

## 常量池

- String: 永久代
- Integer: 堆

## String

- final
  - 不可变对象
  - [Java String类为什么是final的？](https://www.jianshu.com/p/9c7f5daac283)
- String/StringBuilder/StringBuffer
  - String: 在1.8中, 字符串拼接会在编译期自动转化称StringBuilder
  - StringBuilder: 线程不安全
  - StringBuffer: 线程安全    

## io

![IO](http://www.runoob.com/wp-content/uploads/2013/12/iostream2.png)

### structure

- FileInputStream
  - byte
  - extend
    - InputStream
  - constructor
    - public FileInputStream(String name) throws FileNotFoundException
    - public FileInputStream(File file) throws FileNotFoundException
	- public FileInputStream(FileDescriptor fdObj)
- FilterInpuStream
  - byte
  - decorator
    - add filter func to InputStream
  - extend
    - InputStream
  - constructor
    - protected FilterInputStream(InputStream in)
- StringBufferedInputStream
  - byte
  - deprecated
  - extend
    - InputStream
  - constructor
    - public StringBufferInputStream(String s)
- ByteArrayInputStream
  - byte
  - extend
    - InputStream
  - constructor
    - public ByteArrayInputStream(byte buf[])
	- public ByteArrayInputStream(byte buf[], int offset, int length)	
- SocketInputStream
  - byte
  - extend
    - FileInputStream
  - constructor
    - SocketInputStream(AbstractPlainSocketImpl impl) throws IOException
- BufferedReader
  - character
  - decorator
    - add buffer func to Reader
  - extend
    - Reader
  - constructor
    - public BufferedReader(Reader in, int sz)
	- public BufferedReader(Reader in)
- InputStreamReader
  - character
  - extend
    - Reader
  - constructor
    - public InputStreamReader(InputStream in)
	- public InputStreamReader(InputStream in, String charsetName)
	- public InputStreamReader(InputStream in, Charset cs)
	- public InputStreamReader(InputStream in, CharsetDecoder dec)
- FileReader
  - character
  - extend
    - InputStreamReader
  - constructor
    - public FileReader(String fileName) throws FileNotFoundException
	- public FileReader(File file) throws FileNotFoundException
	- public FileReader(FileDescriptor fd)
- StringReader
  - character
  - extend
    - Reader
  - constructor
    - public StringReader(String s)

### System

- in
  - standard input stream
  - InputStream
    - read
- out
  - standard output stream
  - PrintStream
    - write
	- print
	- println
- err
  - standard error output stream
  - PrintStream
    - write
	- print
	- println
	
### Scanner (java5)

- next

```java
import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("enter your name: ");
        if (scanner.hasNext()) {
            String str = scanner.next();
            System.out.println("your name is " + str);
        }
        scanner.close();
    }
}
```

- nextLine

```java
import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("enter your name: ");
        if (scanner.hasNextLine()) {
            String str = scanner.nextLine();
            System.out.println("your name is " + str);
        }
        scanner.close();
    }
}
```

## net

- [basic](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java/net/basic)
- [tcp](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/net/TcpServer.java)
- [http](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/net/HttpServer.java)
- [multithread](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/net/MTServer.java)

## nio

### big picture

- nio: select
- Reactor Streams, Reactor, ReactiveX: reactor
- netty, mina: twisted
- Vert.x
- picothread, kilim, quasar: greenlet

### 1

- [buffer and channel](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java/nio/1/buffer%20and%20channel)
- [selector](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java/nio/1/selector)

### 2

- [selector](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java/nio/2/selector)
- [selector-state](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java/nio/2/selector-state)
- [selector-callback](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java/nio/2/selector-callback)

### reference

- [Java NIO Tutorial](http://tutorials.jenkov.com/java-nio/index.html)
- [mina-netty-twisted](https://github.com/wucao/mina-netty-twisted)
- [Linux进程间内存共享机制mmap详解](https://blog.csdn.net/maverick1990/article/details/48050975)

## multithread

### basic

- [Thread](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/Main1.java)
- [Runnable](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/Main2.java)

### threadpool

- `Executors`: factory to create `ThreadPoolExecutor` 
- `ExecutorService`: implements `Executor`, base class of `ThreadPoolExecutor`
  - shutdown
  - shutdownNow
  - awaitTermination
  - isShutdown
  - isTerminated
  - execute
  - submit
  - invokeAll
  - invokeAny
- [execute](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/Main3.java)
- [submit/invokeAny](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/Main4.java)
- [submit/invokeAll](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/Main5.java)

### synchronization

- without synchronization
  - [without synchronization](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/Main6.java)
- synchronized
  - [method](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/Main7.java)
  - [block/same object](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/Main8.java)
  - [block/different object](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/Main9.java)
  - [block/same object](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/Main10.java)
  - [block/same object](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/Main11.java)
  - [block/different object](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/Main12.java)
- atomic
  - [atomic](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/Main13.java)
- locks
  - [locks](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/Main14.java)
- threadlocal
  - [threadlocal](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/Main15.java)

### api

- concurrent
  - atomic
    - AtomicInteger
    - LongAdder
    - LongAccumulator
  - locks
    - ReentrantLock (Lock)
    - ReentrantReadWriteLock (ReadWriteLock)
    - StampedLock
  - other
    - ExecutorService
    - Executors
    - Callable
    - Future
    - Semaphore
    - ConcurrentMap
    - ConcurrentHashMap

### map

- [HashMap/get](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/Main16.java)
- [HashMap/put](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/Main17.java)
- [ConcurrentHashMap/get](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/Main18.java)
- [ConcurrentHahsMap/put](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/Main19.java)

### singleton

- [eager singleton/thread safe](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/singleton/Singleton1.java)
- [lazy singleton/unthread safe](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/singleton/Singleton2.java)
- [lazy singleton/thread safe/synchronized](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/singleton/Singleton3.java)
- [lazy singleton/unthread safe/double check](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/singleton/Singleton4.java)
- [lasy singleton/thread safe/double check](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/singleton/Singleton5.java)
- [lazy singleton/thread safe/class load](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/singleton/Singleton6.java)
- [lazy singleton/thread safe/enum](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/multithread/singleton/Main.java)

### reference

- [Java多线程学习（吐血超详细总结）](https://www.cnblogs.com/GarfieldEr007/p/5746362.html)
- [Java中的多线程你只要看这一篇就够了](https://www.jianshu.com/p/40d4c7aebd66)
- [A Guide to the Java ExecutorService](http://www.baeldung.com/java-executor-service-tutorial)
- [Java 8 Concurrency Tutorial: Threads and Executors](http://winterbe.com/posts/2015/04/07/java8-concurrency-tutorial-thread-executor-examples/)
- [深入理解Java枚举类型(enum)](https://blog.csdn.net/javazejian/article/details/71333103)
- [JAVA 单例双重检查(double check)为什么不好用](https://blog.csdn.net/anjxue/article/details/51038466)
- [SimpleDateFormat线程不安全及解决办法](https://blog.csdn.net/zdp072/article/details/41044059)

## collection

### simple collection

![simple collection](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/collection/simple%20collection.png)

### complex collection

![complex collection](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/collection/complex%20collection.png)

### concurrent

- [Java中各种集合（字符串类）的线程安全性！！！](https://www.cnblogs.com/yjd_hycf_space/p/7760248.html)

### queue

- Queue
  - interface
  - extends
    - Collection
  - api
    - add
	- remove
- AbstractQueue
  - abstract class
  - extends
    - AbstractCollection
  - implements
    - Queue
- PriorityQueue
  - class
  - extends
    - AbstractQueue
  - implements
    - Serializable
- Deque
  - interface
  - extends
    - Queue
  - api
    - addFirst
	- addLast
	- removeFirst
	- removeLast
- LinkedList
  - Based on linked list. The basic unit is an inner nested class `Node`, which contains `item`, `next`, `prev`
  - class
  - extends
    - AbstractSequentialList
  - implements
    - List
	- Deque
	- Cloneable
	- Serializable
  - api
    - linkFirst: insert node before first node
	- linkLast: insert node after last node
	- unlinkFirst: remove first node
	- unlinkLast: remove last node
	- add: linkLast
	- addFirst: linkFirst
	- addLast: linkLast
	- remove: removeFirst
	- removeFirst: unlinkFirst
	- removeLast: unlinkLast
- ArrayDeque
  - Based on array. All elements are stored in `elements`, and `head` refers to the index of first element, `tail` refers to the index which passes last element.
  - class
  - extends
    - AbstractCollection
  - implements
    - Deque
	- Cloneable
	- Serializable
  - api
    - doubleCapacity: if head equals tail, double the length of elements
    - add: addLast
	- addFirst: assign head-1 to head, add element in head-1 
	- addLast: add element in tail, assign tail+1 to tail
	- remove: removeFirst
	- removeFirst: pollFirst
	- removeLast: pollLast
	- pollFirst: assign null to the element at head, move head to head+1 
	- pollLast: move tail to tail+1, assign null to the element at tail
- concurrent
  - [java队列——queue详细分析](https://www.cnblogs.com/lemon-flm/p/7877898.html)

### map

- TreeMap: binary tree --> balanced binary tree --> red-black tree
- HashMap
  - basic
    - [java提高篇（二三）-----HashMap](https://www.cnblogs.com/chenssy/p/3521565.html)
    - [Java8系列之重新认识HashMap](http://www.importnew.com/20386.html)
    - [HashMap](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/collection/HashMap.md)
  - complexity
    - [面试中关于HashMap的时间复杂度O(1)的思考](https://blog.csdn.net/donggua3694857/article/details/64127131)
    - [java中hashmap容器实现查找O(1)时间复杂度的思考](https://blog.csdn.net/u014633283/article/details/48549155)

  - concurrent
    - [Java HashMap的死循环](https://blog.csdn.net/xiaohui127/article/details/11928865)
    - [面试必备：HashMap、Hashtable、ConcurrentHashMap的原理与区别](https://www.cnblogs.com/heyonggang/p/9112731.html)
  - 说明
      - 实现
        - 1.7: 数组 + 链表
        - 1.8: 数组 + 链表/红黑树
      - rehash/resize
        - 无: 安排在一个桶的链表/红黑树内
        - 有: 当size大于threshold时，触发rehash/resize
      - 复杂度
        - 分散均匀: 复杂度O(1)
        - 分散不匀: 链表复杂度O(n)，红黑树复杂度O(log n)
      - rehash/resize导致线程不安全
- HashTable
  - 说明
    - 实现
      - 加锁
- ConcurrentHahsMap
  - basic
    - [ConcurrentHashMap 1.7和1.8区别](https://blog.csdn.net/xingxiupaioxue/article/details/88062163)
    - [深入浅出ConcurrentHashMap1.8](https://www.jianshu.com/p/c0642afe03e0)
    - [谈谈ConcurrentHashMap1.7和1.8的不同实现](https://www.jianshu.com/p/e694f1e868ec)
    - [深入理解Java——ConcurrentHashMap源码的分析(JDK1.8)](https://zhuanlan.zhihu.com/p/63629645)
    - [ConcurrentHashMap基于JDK1.8源码剖析](https://zhuanlan.zhihu.com/p/35668936)
    - [高并发编程系列：深入探讨ConcurrentHashMap的实现原理(JDK1.7和JDK1.8)](https://zhuanlan.zhihu.com/p/49754357)
  - 说明
    - 实现
      - 1.7: 分段锁
      - 1.8: 细粒度锁 + volatile + cas

### array and list

- ArrayList
  - concurrent
    - [为什么说ArrayList是线程不安全的？](https://blog.csdn.net/u012859681/article/details/78206494)

```java
import java.util.*;

public class Test {
    public static void main(String[] args) {
        List<String> list = Arrays.asList("1", "2", "3");
        Object[] array1 = list.toArray();
        String[] array2 = new String[list.size()];
        String[] array3 = new String[]{"1", "2"};
    }
}
```

```java
import java.util.*;

public class Test {
    public static void main(String[] args) {
        String[] array = new String[]{"1", "2", "3"};
        List<String> list1 = new ArrayList<>();
        list1.add("1"); list1.add("2"); list1.add("3");
        List<String> list2 = new ArrayList<>();
        list2.addAll(list1);
        List<String> list3 = Arrays.asList(array);
        List<String> list4 = Arrays.asList("1", "2", "3");
    }
}
```

### set

```java
import java.util.*;

public class Test {
    public static void main(String[] args) {
        Set<String> set = new HashSet<>();
        set.add("1");
        set.add("2");
        set.add("3");
        set.remove("1");
        System.out.println(set);
    }
}
```

## iterable, iterator

- iterable: java.lang, interface and contain iterator
- iterator: java.util, interface

## comparable, comparator

- comparable: java.lang, `Collections.sort(List<Comparable>)`
- comparator: java.util, `Collections.sort(List<T>, Comparator)`

## garbage collection

### big picture

- copy gc
- tracing gc: java
  - mark sweep
  - mark compaction
- reference counting: python
- generation of grabage collection: combination of gc

### reference

- [sweeterer的博客](https://blog.csdn.net/sweeterer/article/category/6454712)
- [垃圾回收机制中，引用计数法是如何维护所有对象引用的？](https://www.zhihu.com/question/21539353)
- [引用计数法在JVM的GC过程中是否可用？](https://www.zhihu.com/question/52979724)

## reference

### big picture

- strong reference
- weak reference
- soft reference
- phantom reference

## adapter pattern

### intuition

```
            +---------+
input1 ===> |         | ===> output1
            | adapter |
input2 ===> |         | ===> output2
            +---------+
```

### scenario

- compatible with old interface
- multiple inputs and multiple outputs

### method

![adapter pattern](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/adapter%20pattern/adapter%20pattern.jpg)

### reference

- [适配器模式](http://www.runoob.com/design-pattern/adapter-pattern.html)
- [设计模式(二) 三种适配器模式 总结和使用场景](http://blog.csdn.net/zxt0601/article/details/52848004)

## decorator pattern

### intuition

```
+-------+
| func2 |
+-------+
| func1 |
+-------+
| basic |
+-------+
```

### scenario

- add function to basic

### method

![decorator pattern](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/decorator%20pattern/decorator%20pattern.jpg)

### reference

- [装饰器模式](http://www.runoob.com/design-pattern/decorator-pattern.html)
- [java中什么是装饰者模式?](https://www.zhihu.com/question/32007641)
- [装饰者模式及其应用](http://blog.csdn.net/gdutxiaoxu/article/details/51885105)

## proxy pattern

### intuition

```
realsubject <---> proxy <--- client 
```

### scenario

- proxy to realsubject to communicate with client

### method

![proxy pattern](https://github.com/gaoxinge/something/blob/master/learn%20java/learn%20java/proxy%20pattern/proxy%20pattern.png)

### implementation

- 静态代理: AspectJ
  - 代码: 类要有对应的接口，一个接口对应一个代理类
- 动态代理: Spring AOP（面向切面编程）
  - JDK: 反射 / 类要有对应的接口
  - CGLib: ASM

### reference

- [Spring基础（九）：代理模式介绍](https://bbs.huaweicloud.com/blogs/387578)
- [【关于Spring那些事】——带你了解Spring AOP的代理模式](https://developer.aliyun.com/article/888998)
- [3种代理模式-理解Spring Aop](https://juejin.cn/post/6844903853813563405)
- [Spring的AOP理解](https://zhuanlan.zhihu.com/p/142578216)

## factory pattern

### intuition

```
interface A           factory
  ^       ^               |
  |       |               |
class A1 class A2         |
  ^       ^               |
  |       |               |
  a1      a2 <------------|
  ^                       |
  |-----------------------|
```

### scenario

- factory produce the instance of different class which implement same interface

## singleton pattern

```java
public class Config {
    private static Config instance;
    private Config() {}
    public static Config getInstance() {
        if (instance == null)
            instance = new Config();
        return instance;
    }
    
}
```

## visitor pattern

### override

```java
interface Animal {
    void speak();
}

class Cat implements Animal {
    @Override
    public void speak() {
        System.out.println("cat speak");
    }
}

class Dog implements Animal {
    @Override
    public void speak() {
        System.out.println("dog speak");
    }
}

class Fox implements Animal {
    @Override
    public void speak() {
        System.out.println("fox speak");
    }
}


class Speaker {
    public void speak(Animal a) {
        a.speak();
    }
}


public class Main {
    public static void main(String[] args) {
        Animal[] animals = {new Dog(), new Cat(), new Fox()};
        Speaker s = new Speaker();
        for (Animal animal: animals)
            s.speak(animal);
    }
}
```

### speaker

```java
interface Animal {
    void speak(Speaker s);
}

class Cat implements Animal {
    @Override
    public void speak(Speaker s) {
        s.speak(this);
    }
}

class Dog implements Animal {
    @Override
    public void speak(Speaker s) {
        s.speak(this);
    }
}

class Fox implements Animal {
    @Override
    public void speak(Speaker s) {
        s.speak(this);
    }
}


class Speaker {
    public void speak(Animal a) {
        a.speak(this);
    }
    
    public void speak(Cat a) {
        System.out.println("cat speak");
    }
    
    public void speak(Dog d) {
        System.out.println("dog speak");
    }
    
    public void speak(Fox f) {
        System.out.println("fox speak");
    }
}


public class Main {
    public static void main(String[] args) {
        Animal[] animals = {new Dog(), new Cat(), new Fox()};
        Speaker s = new Speaker();
        for (Animal animal: animals)
            s.speak(animal);
    }
}
```

### visitor

```java
interface Animal {
    void accept(Visitor v);
}

class Cat implements Animal {
    @Override
    public void accept(Visitor v) {
        v.visit(this);
    }
}

class Dog implements Animal {
    @Override
    public void accept(Visitor v) {
        v.visit(this);
    }
}

class Fox implements Animal {
    @Override
    public void accept(Visitor v) {
        v.visit(this);
    }
}


interface Visitor {
    void visit(Animal a);
    void visit(Dog d);
    void visit(Cat c);
    void visit(Fox f);
}

class Speaker implements Visitor {
    public void visit(Animal a) {
        a.accept(this);
    }
    
    public void visit(Cat a) {
        System.out.println("cat speak");
    }
    
    public void visit(Dog d) {
        System.out.println("dog speak");
    }
    
    public void visit(Fox f) {
        System.out.println("fox speak");
    }
}

class Runner implements Visitor {
    public void visit(Animal a) {
        a.accept(this);
    }
    
    public void visit(Cat a) {
        System.out.println("cat run");
    }
    
    public void visit(Dog d) {
        System.out.println("dog run");
    }
    
    public void visit(Fox f) {
        System.out.println("fox run");
    }
}


public class Main {
    public static void main(String[] args) {
        Animal[] animals = {new Dog(), new Cat(), new Fox()};
        Speaker s = new Speaker();
        Runner r = new Runner();
        for (Animal animal: animals)
            s.visit(animal);
        for (Animal animal: animals)
            r.visit(animal);
    }
}
```

## reference

- [进击的Java新人](https://zhuanlan.zhihu.com/hinus)
- [content](https://zhuanlan.zhihu.com/p/24393775)
