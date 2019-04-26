# generic in java

- [generics](https://docs.oracle.com/javase/tutorial/java/generics/index.html)

## generic

### generic type

```java
public class Pair<K, V> {

    private K key;
    private V value;

    public Pair(K key, V value) {
        this.key = key;
        this.value = value;
    }

    public void setKey(K key) { this.key = key; }
    public void setValue(V value) { this.value = value; }
    public K getKey()   { return key; }
    public V getValue() { return value; }
}
```

### generic method

```java
public class Util {
    public static <K, V> boolean compare(Pair<K, V> p1, Pair<K, V> p2) {
        return p1.getKey().equals(p2.getKey()) &&
               p1.getValue().equals(p2.getValue());
    }
}
```

## bounded type parameters

```java
public class Test {
    public static void main(String[] args) {
        Box<Integer> integerBox = new Box<Integer>();
        integerBox.set(10);
        integerBox.inspect(11);
        integerBox.inspect("some text"); // compile error
    }
}

class Box<T> {
    private T t;
    
    public void set(T t) {
        this.t = t;
    }
    
    public T get() {
        return t;
    }
    
    public <U extends Number> void inspect(U u) {
        System.out.println("T: " + t.getClass().getName());
        System.out.println("U: " + u.getClass().getName());
    }
}
```

### multiple bounds

```java
class     A {}
interface B {}
interface C {}

class D1<T extends A & B & C>         {}
class D2<T extends A implements B, C> {} // compile error
```

### use specific variable and method of type parameters

```java
public class Main {
    // compile error: because Object doesn't have add method
    public static <T> T add(T o1, T o2) {
        return o1.add(o2);
    }
}
```

```java
public class Main {
    public static <T extends Addable<T>> T add(T o1, T o2) {
        return o1.add(o2);
    }
	
    public static void main(String[] args) {
        A a = new A(1);
        A b = new A(2);
        A c = add(a, b);
        System.out.println(c.a);
    }
}

interface Addable<T> {
    T add(T o1);
}

class A implements Addable<A> {
    Integer a;
    
    A (Integer a) {
        this.a = a;
    }
    
    @Override
    public A add(A other) {
        return new A(this.a + other.a);
    }
}
```

## wildcard

### unbounded wildcard

```java
import java.util.*;

public class Test {
    // only print List<Object>, can't print
    // List<Integer>, List<String>, List<Double>
    public static void printList_(List<Object> list) {
        for (Object elem: list)
            System.out.print(elem + " ");
        System.out.println();
    }
    
    public static void printList(List<?> list) {
        for (Object elem: list)
            System.out.print(elem + " ");
        System.out.println();
    }
    
    public static void main(String[] args) {
        List<Integer> li = Arrays.asList(1, 2, 3);
        List<String>  ls = Arrays.asList("one", "two", "three");
        printList(li);
        printList(ls);
    }
}
```

### upper bounded wildcard

```java
public static double sumOfList(List<? extends Number> list) {
    double s = 0.0;
    for (Number n : list)
        s += n.doubleValue();
    return s;
}
```

### lower bounded wildcard

```java
public static void addNumbers(List<? super Integer> list) {
    for (int i = 1; i <= 10; i++) {
        list.add(i);
    }
}
```

### subtype

```java
import java.util.*;

/****************************************************
 * ?           := CAP#1
 * ? extends B := CAP#2
 * ? extends C := CAP#3
 ****************************************************
 * Object  <---  B  <--- C
 *   ^           ^       ^
 *   |           |       |
 * CAP#1       CAP#2   CAP#3
 ****************************************************
 * List<CAP#1>  <---  List<CAP#2>  <---  List<CAP#3>
 *                        ^                  ^                    
 *                        |                  |
 *                       List<B>            List<C>
 ****************************************************/
public class Test {    
    public static List<? extends B> f(int a) {
        List<B> l1 = new ArrayList<>();
        List<C> l2 = new ArrayList<>();
        l1.add(new B(1));
        l2.add(new C(1, 2));
        if (a > 0) return l1;
        else       return l2;
    }
    
    public static void main(String[] args) {
        /* relationship between B and C*/
        // compile ok: b1 will use the method getX of C 
        //             if C has method getX
        // B b1 = new C(1, 2);
        // System.out.println(b1.getX());
        
        // compile error: B has no method getY
        // B b1 = new C(1, 2);
        // System.out.println(b1.getY());
        
        // compile ok: C ---> B without cast, but 
        //             B ---> C with cast
        // B b1 = new C(1, 2);
        // C b2 = (C) b1;
        //System.out.println(b2.getY());
        
        /* relationship refer to wildcard */
        List<? extends B> t1 = f(1);
        List<? extends B> t2 = f(-1);
        
        // compile error: can not convert CAP#2 to B, C
        t1.add(new B(1));
        t2.add(new C(1, 2));
        
        // B, C
        System.out.println(t1.get(0).getClass().getName());
        System.out.println(t2.get(0).getClass().getName());
        
        // compile ok
        List<? extends B> t3 =           f(0);
        List<B>           t4 = (List<B>) f(1);
        List<C>           t5 = (List<C>) f(-1);
        System.out.println(t3.get(0).getX());
        System.out.println(t4.get(0).getX());
        System.out.println(t5.get(0).getY());
    }
}

class B {
    private Integer x;
    public B(Integer x) {this.x = x;}
    public Integer getX() {return this.x;}
    public void setX(Integer x) {this.x = x;}
}

class C extends B {
    private Integer y;
    public C(Integer x, Integer y) {
        super(x);
        this.y = y;
    }
    public Integer getY() {return this.y;}
    public void setY(Integer y) {this.y = y;}
}
```

### wildcard capture and helper methods

```java
public class WildcardError {
    // set: can not convert Object to CAP#1  
    void foo(List<?> i) {
        i.set(0, i.get(0));
    }
}
```

```java
public class WildcardFixed {
    void foo(List<?> i) {
        fooHelper(i);
    }

    private <T> void fooHelper(List<T> l) {
        l.set(0, l.get(0));
    }
}
```