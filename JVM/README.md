# JVM

## java

```
> javac Main.java
> javap -v -p -s -sysinfo -constants Main.class > Main.txt
```

```java
public class Main {
    public static void main(String[] args) {
        System.out.println("Hello World!");
    }
}
```

```
Classfile /C:/Users/xg.gao/Desktop/Main.class
  Last modified 2018-7-15; size 414 bytes
  MD5 checksum 7fcef1c80a4368742edf50013b5c7e02
  Compiled from "Main.java"
public class Main
  minor version: 0
  major version: 52
  flags: ACC_PUBLIC, ACC_SUPER
Constant pool:
   #1 = Methodref          #6.#15         // java/lang/Object."<init>":()V
   #2 = Fieldref           #16.#17        // java/lang/System.out:Ljava/io/PrintStream;
   #3 = String             #18            // Hello World!
   #4 = Methodref          #19.#20        // java/io/PrintStream.println:(Ljava/lang/String;)V
   #5 = Class              #21            // Main
   #6 = Class              #22            // java/lang/Object
   #7 = Utf8               <init>
   #8 = Utf8               ()V
   #9 = Utf8               Code
  #10 = Utf8               LineNumberTable
  #11 = Utf8               main
  #12 = Utf8               ([Ljava/lang/String;)V
  #13 = Utf8               SourceFile
  #14 = Utf8               Main.java
  #15 = NameAndType        #7:#8          // "<init>":()V
  #16 = Class              #23            // java/lang/System
  #17 = NameAndType        #24:#25        // out:Ljava/io/PrintStream;
  #18 = Utf8               Hello World!
  #19 = Class              #26            // java/io/PrintStream
  #20 = NameAndType        #27:#28        // println:(Ljava/lang/String;)V
  #21 = Utf8               Main
  #22 = Utf8               java/lang/Object
  #23 = Utf8               java/lang/System
  #24 = Utf8               out
  #25 = Utf8               Ljava/io/PrintStream;
  #26 = Utf8               java/io/PrintStream
  #27 = Utf8               println
  #28 = Utf8               (Ljava/lang/String;)V
{
  public Main();
    descriptor: ()V
    flags: ACC_PUBLIC
    Code:
      stack=1, locals=1, args_size=1
         0: aload_0
         1: invokespecial #1                  // Method java/lang/Object."<init>":()V
         4: return
      LineNumberTable:
        line 1: 0

  public static void main(java.lang.String[]);
    descriptor: ([Ljava/lang/String;)V
    flags: ACC_PUBLIC, ACC_STATIC
    Code:
      stack=2, locals=1, args_size=1
         0: getstatic     #2                  // Field java/lang/System.out:Ljava/io/PrintStream;
         3: ldc           #3                  // String Hello World!
         5: invokevirtual #4                  // Method java/io/PrintStream.println:(Ljava/lang/String;)V
         8: return
      LineNumberTable:
        line 3: 0
        line 4: 8
}
SourceFile: "Main.java"
```

## big picture

![1](https://github.com/gaoxinge/something/blob/master/JVM/1.png)
![2](https://github.com/gaoxinge/something/blob/master/JVM/2.png)

## permanent generation 

- method area
- interned string

## heap

Heap is used to store object, and divided into three spaces:

- Young Generation
  - Eden Sapce
  - Suvivor Space
- Old Generation

Accroding to the object's frequency, JVM will transfer object from one space to another like

```
Young Generation (Eden Space) ---> Young Generation (Suvivor Space) ---> Old Generation
```

## thread

- pc
- JVM stack
  - stack frame
    - local variables
    - return value
    - operand stack
    - current class constant pool reference
- native stack

## class loader

### process

- loading
- linking
  - verfying
  - preparing
  - resolving
- initialization

### type

- bootstrap class loader
- extension class loader
- system class loader
- user defined class loader

### result

```
class loader object
class object        (heap) ---> class info (method area)
```

## object

```
object reference (thread) ---> object (heap)
```

## current class constant pool

```
current class constant pool referenct (thread) ---> class info (method area)
```

## garbage collection

- [垃圾回收](https://github.com/crossoverJie/Java-Interview/blob/master/MD/GarbageCollection.md)

![3](https://github.com/gaoxinge/something/blob/master/JVM/3.png)

## dynamic linking

- class file
- class info (method area)
- class loader (heap)
- class (heap)

## oop

- struct (native heap)

## stack

- struct (native heap)

## interpreter

- native stack
- native main thread: use interpreter to consume the byte code in main, which in some class
- native sub thread: use interpreter to consume the byte code in thread.run, which in some class

## jvm

- javac (elf)

## JDK8

- 永久带移除
- 使用MetaSapce保存类加载之后的类信息
- 字符串常量池被移动到Java堆

## ASM

- [ASM](https://asm.ow2.io/)
- lombok
- cglib
- quasar

## string intern

- [几张图轻松理解String.intern()](https://blog.csdn.net/soonfly/article/details/70147205)

## JNI

- [Java基础：认识&理解关键字native实战篇](https://www.cnblogs.com/Alandre/p/4456719.html)
- [Java Native Interface (JNI)](https://www3.ntu.edu.sg/home/ehchua/programming/java/JavaNativeInterface.html)
- [JNA](https://github.com/java-native-access/jna)

## reference

- [Java虚拟机的堆、栈、堆栈如何去理解？](https://www.zhihu.com/question/29833675)
- [JVM堆栈和C/C++堆栈的关系是什么？](https://www.zhihu.com/question/40122222)
- [Stack and Heap memory in Java](https://softwareengineering.stackexchange.com/questions/65281/stack-and-heap-memory-in-java)
- [Stack vs Heap in C/Java](https://stackoverflow.com/questions/17535436/stack-vs-heap-in-c-java)
- [How does Java (JVM) allocate stack for each thread](https://stackoverflow.com/questions/36898701/how-does-java-jvm-allocate-stack-for-each-thread)
- [JVM Stacks and Stack Frames](https://alvinalexander.com/scala/fp-book/recursion-jvm-stacks-stack-frames)
- [The Java Virtual Machine](https://www.artima.com/insidejvm/ed2/jvm.html)
- [Run-time Stack mechanism in Java](https://www.geeksforgeeks.org/run-time-stack-mechanism-java/)
- [Java Virtual Machine (JVM) Stack Area](https://www.geeksforgeeks.org/java-virtual-machine-jvm-stack-area/)
- [Java Code To Byte Code - Part One](http://blog.jamesdbloom.com/JavaCodeToByteCode_PartOne.html)
- [JVM Internals](http://blog.jamesdbloom.com/JVMInternals.html)
- [JAVA类的加载、连接与初始化](https://www.cnblogs.com/Blogyin/p/7809382.html)
- [一看你就懂，超详细java中的ClassLoader详解](https://blog.csdn.net/briblue/article/details/54973413)
- [chunyuan314的博客](https://blog.csdn.net/chunyuan314)
- [JVM调优总结 -Xms -Xmx -Xmn -Xss](https://blog.csdn.net/rickyit/article/details/53895060)