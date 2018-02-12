# learn java 8

- release
  - [JDK 8 Is Released!](https://blogs.oracle.com/thejavatutorials/jdk-8-is-released)
- tutorial
  - [Everything about Java 8](https://www.techempower.com/blog/2013/03/26/everything-about-java-8/)
  - [Java 8 Tutorial](http://winterbe.com/posts/2014/03/16/java-8-tutorial/)
  - [Java 8 Tutorial](https://howtodoinjava.com/java-8-tutorial/)
  - [java 8](http://www.baeldung.com/tag/java-8/)
- functional
  - [深入浅出 Java 8 Lambda 表达式](http://blog.oneapm.com/apm-tech/226.html)
  - [深入理解Java 8 Lambda（语言篇——lambda，方法引用，目标类型和默认方法）](http://zh.lucida.me/blog/java-8-lambdas-insideout-language-features/)
  - [深入理解Java 8 Lambda（类库篇——Streams API，Collectors和并行）](http://zh.lucida.me/blog/java-8-lambdas-inside-out-library-features/)

## Functional Interface

```java
public class Test {
    public static void main(String[] args) {
        MathOperation addition = new Addition();
        System.out.println(addition.operation(3.0, 2.0));
        
        MathOperation substraction = new MathOperation() {
            @Override
            public double operation(double a, double b) {
                return a - b;
            }
        };
        System.out.println(substraction.operation(3.0, 2.0));
        
        MathOperation multiplication = (x, y) -> x * y;
        System.out.println(multiplication.operation(3.0, 2.0));
        
        MathOperation division = MathCopy::division;
        System.out.println(division.operation(3.0, 2.0));
    }
}

@FunctionalInterface
interface MathOperation {
    double operation(double a, double b);
    
    default double sqrt(double a) {
        return Math.sqrt(a);
    }
    
    default double square(double a) {
        return a * a;
    }
}

class Addition implements MathOperation {
    @Override
    public double operation(double a, double b) {
        return a + b;
    }
}

class MathCopy {
    public static double division(double a, double b) {
        return a / b;
    }
}
```

## Lambda Expression

```java
import java.util.*;

public class Test {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(4, 5, 6, 1, 2, 3);
        
        list.stream()
            .map(x -> x * x)
            .forEach(x -> System.out.print(x + " "));
        System.out.println();
        
        list.stream()
            .sorted((x, y) -> {
                return x.compareTo(y);
            })
            .forEach(x -> System.out.print(x + " "));
        System.out.println();
        
        list.stream()
            .forEach(x -> {
                Integer y = x * x + 1;
                System.out.print(y + " ");
            });
        System.out.println();
        
        list.stream()
            .sorted((x, y) -> {
                Integer absX = Math.abs(x);
                Integer absY = Math.abs(y);
                return absX.compareTo(absY);
            })
            .forEach(x -> System.out.print(x + " "));
        System.out.println();
    }
}
```

## Method Reference

```java
import java.util.*;

public class Test {
    public static void forEach(List<String> list, Formatter formatter) {
        for (String item: list)
            System.out.print(formatter.format("%s\n", item));
        System.out.println();
    }
    
    public static void main(String[] args) {
        List<String> names = Arrays.asList(
                                "Charlie Brown", 
                                "Snoopy", 
                                "Lucy", 
                                "Linus", 
                                "Woodstock"
                            );
        forEach(names, String::format);
        forEach(names, (fmt, arg) -> String.format(fmt, arg));
    }
}

@FunctionalInterface
interface Formatter {
    String format(String fmtString, Object... arguments);
}
```

```java
import java.util.function.Supplier;

public class Test {
    public static void print(Supplier<String> supplier) {
        System.out.println(supplier.get());
    }
    
    public static void main(String[] args) {
        String s = "method reference are cool";
        print(s::toString);
        print(() -> s.toString());
    }
}
```

```java
import java.util.function.Function;

public class Test {
    public static void print(Function<String, String> function, String value) {
        System.out.println(function.apply(value));
    }
    
    public static void main(String[] args) {
        String s = "some string to be printed";
        print(String::toString, s);
        print(x -> x.toString(), s);
    }
}
```

### reference

- [Java SE 8's New Language Features, Part 2: Predefined Functional Interfaces, Method References, and More](http://www.informit.com/articles/article.aspx?p=2191424&seqNum=2)

## Built-in Functional Interface

### 

- Function

- Predicate

- Consumer

- Supplier

###

- Optional

###

- Comparator

###

- Runnable

### 

- MouseAdapter
- ActionListener

## Stream

### filter

### map

### flatMap

### peek

### distinct

### sorted

### limit

### skip

### forEach

### toArray

### reduce

### collect

### min

### max

### count

### anyMatch

### allMatch

### noneMatch

### findFirst

### findAny

## Date

## Instant

## String

## StringJoiner