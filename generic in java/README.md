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

