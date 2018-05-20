# learn java

- [进击的Java新人](https://zhuanlan.zhihu.com/hinus)
- [content](https://zhuanlan.zhihu.com/p/24393775)

# content

- [static](https://github.com/gaoxinge/something/tree/master/learn%20java#static)
- [final](https://github.com/gaoxinge/something/tree/master/learn%20java#final)
- [data type](https://github.com/gaoxinge/something/tree/master/learn%20java#data-type)
- [primitive type and wrapper type](https://github.com/gaoxinge/something/tree/master/learn%20java#primitive-type-and-wrapper-type)
- [toString](https://github.com/gaoxinge/something/tree/master/learn%20java#tostring)
- [wrapper type and string](https://github.com/gaoxinge/something/tree/master/learn%20java#wrapper-type-and-string)
- [pass parameter by value or by reference](https://github.com/gaoxinge/something/tree/master/learn%20java#pass-parameter-by-value-or-by-reference)
- [IO](https://github.com/gaoxinge/something/tree/master/learn%20java#pass-parameter-by-value-or-by-reference)
- [collection](https://github.com/gaoxinge/something/tree/master/learn%20java#collection)
- [array and list](https://github.com/gaoxinge/something/tree/master/learn%20java#array-and-list)
- [iterable, iterator](https://github.com/gaoxinge/something/tree/master/learn%20java#iterable-iterator)
- [comparable, comparator](https://github.com/gaoxinge/something/tree/master/learn%20java#comparable-comparator)
- [adapter pattern](https://github.com/gaoxinge/something/tree/master/learn%20java#adapter-pattern)
- [decorator pattern](https://github.com/gaoxinge/something/tree/master/learn%20java#adapter-pattern)

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

## IO

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

## collection

### simple collection

![simple collection](https://github.com/gaoxinge/something/blob/master/learn%20java/image/simple%20collection.png)

### complex collection

![complex collection](https://github.com/gaoxinge/something/blob/master/learn%20java/image/complex%20collection.png)

### queue

- Queue
  - iterface
  - extends
    - Collection
  - api
    - add
	- remove
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

### map
  
- TreeMap: binary tree --> balanced binary tree --> red-black tree
    
    
## array and list

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

## iterable, iterator

- iterable: java.lang, interface and contain iterator
- iterator: java.util, interface

## comparable, comparator

- comparable: java.lang, `Collections.sort(List<Comparable>)`
- comparator: java.util, `Collections.sort(List<T>, Comparator)`

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

![adapter pattern](https://github.com/gaoxinge/something/blob/master/learn%20java/image/adapter%20pattern.jpg)

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

![decorator pattern](https://github.com/gaoxinge/something/blob/master/learn%20java/image/decorator%20pattern.jpg)

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

![proxy pattern](https://github.com/gaoxinge/something/blob/master/learn%20java/image/proxy%20pattern.jpg)
 