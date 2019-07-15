# volatile

There are three problems that we should consider when writing a data-shared program:

- atomic
- cache coherence
- instruction rearrangement

## volatile

- volatile don't keep atomic
- volatile is a barrier to guarantee the cache coherence before volatile for all thread 
- volatile is a barrier to avoid the instruction reordering before volatile and after volatile 

## volatile reference vs volatile value

- volatile reference only keep reference volatile, not keep the field volatile
- volatile value keep itself volatile

## volatile vs final

- volatile can assign more than once
- final can only assign once

## reference

- [Java并发编程：volatile关键字解析](https://www.cnblogs.com/dolphin0520/p/3920373.html)
- [JAVA 单例双重检查(double check)为什么不好用](https://blog.csdn.net/anjxue/article/details/51038466)
- [Volatile Arrays in Java](http://jeremymanson.blogspot.com/2009/06/volatile-arrays-in-java.html)
- [Java Volatile Keyword](http://tutorials.jenkov.com/java-concurrency/volatile.html)
- [Why can an Object member variable not be both final and volatile in Java?](https://stackoverflow.com/questions/9328252/why-can-an-object-member-variable-not-be-both-final-and-volatile-in-java)