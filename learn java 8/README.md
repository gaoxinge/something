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
    
    static double square(double a) {
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

### java.util.function

- Function

```java
import java.util.function.Function;

public class Test {
    public static void main(String[] args) {
        Function<String, Integer> f1 = x -> x.length();
        Function<Integer, String> f2 = x -> x.toString();
        System.out.println(f1.apply("123"));
        System.out.println(f2.apply(123));
        
        Function<Integer, Integer> compose1 = f1.compose(f2);
        Function<String, String> compose2 = f1.andThen(f2);
        System.out.println(compose1.apply(123));
        System.out.println(compose2.apply("123"));
        
        Function<String, String> identity1 = Function.identity();
        Function<Integer, Integer> identity2 = Function.identity();
        System.out.println(identity1.apply("123"));
        System.out.println(identity2.apply(123));
    }
}
```

- Predicate

```java
import java.util.function.Predicate;

public class Test {
    public static void main(String[] args) {
        Predicate<String> predicate1 = x -> x.startsWith("a");
        Predicate<String> predicate2 = x -> x.endsWith("a");
        System.out.println(predicate1.test("abcd"));
        System.out.println(predicate2.test("abcd"));
        
        Predicate<String> predicate3 = predicate1.and(predicate2);
        Predicate<String> predicate4 = predicate1.or(predicate2);
        Predicate<String> predicate5 = predicate1.negate();
        System.out.println(predicate3.test("abcd"));
        System.out.println(predicate4.test("abcd"));
        System.out.println(predicate5.test("abcd"));
        
        Predicate<String> predicate6 = Predicate.isEqual(123);
        System.out.println(predicate6.test("abcd"));
    }
}
```

- Consumer

```java
import java.util.function.Consumer;

public class Test {
    public static void main(String[] args) {
        Consumer<Integer> consumer1 = x -> System.out.println(x);
        Consumer<Integer> consumer2 = x -> System.out.println(2 * x);
        Consumer<Integer> consumer3 = consumer1.andThen(consumer2);
        consumer3.accept(123);
    }
}
```

- Supplier

```java
import java.util.function.Supplier;

public class Test {
    public static void main(String[] args) {
        Supplier<Integer> supplier = () -> 12345;
        System.out.println(supplier.get());
    }
}
```

### java.util

- Comparator

```java
import java.util.Comparator;
import java.util.function.Function;

public class Test {
    public static void main(String[] args) {
        Function<String, Integer> function = x -> x.length();
        
        Comparator<Integer> comparator1 = (x, y) -> x.compareTo(y);
        System.out.println(comparator1.compare(1, 2));
        
        Comparator<String> comparator2 = Comparator.comparing(function, comparator1);
        System.out.println(comparator2.compare("123", "4567"));
        
        Comparator<String> comparator3 = Comparator.comparing(function);
        System.out.println(comparator3.compare("123", "4567"));
    }
}
```

### java.lang

- Runnable

```java
import java.lang.Runnable;

public class Test {
    public static void main(String[] args) {
        Runnable runnable = () -> System.out.println("hello world");
        runnable.run();
    }
}
```

## Stream

### filter

```java
import java.util.*;
import java.util.function.*;

public class Test {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(4, 5, 6, 1, 2, 3);
        
        Predicate<Integer> predicate = x -> x > 3; 
        list.stream()
            .filter(predicate)
            .forEach(x -> System.out.print(x + " "));
        System.out.println();
    }
}
```

### map

```java
import java.util.*;
import java.util.function.*;

public class Test {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(4, 5, 6, 1, 2, 3);
        
        Function<Integer, Integer> function = x -> x + 1;
        list.stream()
            .map(function)
            .forEach(x -> System.out.print(x + " "));
        System.out.println();
    }
}
```

### distinct

```java
import java.util.*;
import java.util.function.*;

public class Test {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(4, 5, 6, 1, 2, 3);
        
        list.stream()
            .distinct()
            .forEach(x -> System.out.print(x + " "));
        System.out.println();
    }
}
```

### sorted

```java
import java.util.*;
import java.util.function.*;

public class Test {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(4, 5, 6, 1, 2, 3);
            
        list.stream()
            .sorted()
            .forEach(x -> System.out.print(x + " "));
        System.out.println();
            
        Comparator<Integer> comparator = (x, y) -> x.compareTo(y);
        list.stream()
            .sorted(comparator)
            .forEach(x -> System.out.print(x + " "));
        System.out.println();
    }
}
```

### peak

```java
import java.util.*;
import java.util.function.*;

public class Test {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(4, 5, 6, 1, 2, 3);
        
        Consumer<Integer> consumer = x -> System.out.print(2 * x);
        list.stream()
            .peek(consumer)
            .forEach(x -> System.out.print(x + " "));
        System.out.println();
    }
}
```

### limit

```java
import java.util.*;
import java.util.function.*;

public class Test {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(4, 5, 6, 1, 2, 3);
        
        list.stream()
            .limit(3)
            .forEach(x -> System.out.print(x + " "));
        System.out.println();
    }
}
```

### skip

```java
import java.util.*;
import java.util.function.*;

public class Test {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(4, 5, 6, 1, 2, 3);
        
        list.stream()
            .skip(3)
            .forEach(x -> System.out.print(x + " "));
        System.out.println();
    }
}
```

### forEach

```java
import java.util.*;
import java.util.function.*;

public class Test {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(4, 5, 6, 1, 2, 3);
        
        list.forEach(x -> System.out.print(x + " "));
        System.out.println();
        
        list.stream()
            .forEach(x -> System.out.print(x + " "));
        System.out.println();
    }
}
```

### toArray

```java
import java.util.*;
import java.util.function.*;

public class Test {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(4, 5, 6, 1, 2, 3);
        
        Object[] array1 = list.toArray();
        for (Object o: array1)
            System.out.print(o + " ");
        System.out.println();
        
        Integer[] array2 = new Integer[list.size()];
        Integer[] array3 = list.toArray(array2);
        for (Integer i: array2)
            System.out.print(i + " ");
        System.out.println();
        for (Integer i: array3)
            System.out.print(i + " ");
        System.out.println();
        
        Object[] array4 = list.stream()
                              .toArray();
        for (Object o: array4)
            System.out.print(o + " ");
        System.out.println();
        
        IntFunction<Integer[]> intFunction = x -> {
                                                Integer[] array = new Integer[x]; 
                                                for (int i = 0; i < x && i < list.size(); ++i)
                                                    array[i] = list.get(i);
                                                return array;
                                            };
        Integer[] array5 = list.stream().toArray(intFunction);
        for (Integer i: array5)
            System.out.print(i + " ");
        System.out.println();
    }
}
```

### reduce

```java
import java.util.*;
import java.util.function.*;

public class Test {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(4, 5, 6, 1, 2, 3);
        
        BinaryOperator<Integer> binaryOperator1 = (x, y) -> x + y;
        Integer sum1 = list.stream()
                           .reduce(0, binaryOperator1);
        System.out.println(sum1);
        
        BinaryOperator<Integer> binaryOperator2 = (x, y) -> x + y;
        Optional<Integer> sum2 = list.stream()
                           .reduce(binaryOperator2);
        System.out.println(sum2.get());
    
        BiFunction<String, Integer, String> biFunction = (x, y) -> x + y;
        BinaryOperator<String> binaryOperator3 = (x, y) -> x + y;
        String sum3 = list.stream()
                          .reduce("a", biFunction, binaryOperator3);
        System.out.println(sum3);
    }
}
```

### collect

```java
import java.util.*;
import java.util.function.*;
import java.util.stream.*;

public class Test {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(4, 5, 6, 1, 2, 3);
        
        List<Integer> l = list.stream()
                              .collect(Collectors.toList());
        System.out.println(l);
        
        Set<Integer> s = list.stream()
                             .collect(Collectors.toSet());
        System.out.println(s);
        
        Function<Integer, Integer> function = x -> x % 2;
        Map<Integer, List<Integer>> m = list.stream()
                                            .collect(Collectors.groupingBy(function));
        System.out.println(m);
    }
}
```

### min

```java
import java.util.*;
import java.util.function.*;

public class Test {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(4, 5, 6, 1, 2, 3);
        Comparator<Integer> comparator = (x, y) -> x.compareTo(y);
        Optional<Integer> min = list.stream().min(comparator);
        System.out.println(min.get());
    }
}
```

### max

```java
import java.util.*;
import java.util.function.*;

public class Test {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(4, 5, 6, 1, 2, 3);
        Comparator<Integer> comparator = (x, y) -> x.compareTo(y);
        Optional<Integer> max = list.stream().max(comparator);
        System.out.println(max.get());
    }
}
```

### count

```java
import java.util.*;
import java.util.function.*;

public class Test {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(4, 5, 6, 1, 2, 3);
        System.out.println(list.stream().count());
    }
}
```

### anyMatch

```java
import java.util.*;
import java.util.function.*;

public class Test {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(4, 5, 6, 1, 2, 3);
        Predicate<Integer> predicate = x -> x == 0;
        System.out.println(list.stream().anyMatch(predicate));
    }
}
```

### allMatch

```java
import java.util.*;
import java.util.function.*;

public class Test {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(4, 5, 6, 1, 2, 3);
        Predicate<Integer> predicate = x -> x == 0;
        System.out.println(list.stream().allMatch(predicate));
    }
}
```

### noneMatch

```java
import java.util.*;
import java.util.function.*;

public class Test {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(4, 5, 6, 1, 2, 3);
        Predicate<Integer> predicate = x -> x == 0;
        System.out.println(list.stream().noneMatch(predicate));
    }
}
```

### findFirst

```java
import java.util.*;
import java.util.function.*;

public class Test {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(4, 5, 6, 1, 2, 3);
        Optional<Integer> first = list.stream().findFirst();
        System.out.println(first.get());
    }
}
```

### findAny

```java
import java.util.*;
import java.util.function.*;

public class Test {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(4, 5, 6, 1, 2, 3);
        Optional<Integer> first = list.stream().findAny();
        System.out.println(first.get());
    }
}
```

## Date

```java
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeFormatterBuilder;
import java.time.temporal.ChronoField;

public class Test {
    public static void main(String[] args) {
        // LocalDate
        LocalDate date1 = LocalDate.parse("2017-02-14");
        LocalDate date2 = LocalDate.now();
        System.out.println(date1.plusDays(1));
        System.out.println(date1.isAfter(date2));
        
        // LocalDateTime
        LocalDateTime dateTime1 = LocalDateTime.parse("2017-02-14T00:00:00.000");
        LocalDateTime dateTime2 = LocalDateTime.now();
        System.out.println(dateTime1.plusDays(1));
        System.out.println(dateTime1.isAfter(dateTime2));
        
        // DateTimeFormatter
        DateTimeFormatter df1 = DateTimeFormatter.ofPattern("dd MM yyyy");
        DateTimeFormatterBuilder dfBuilder = new DateTimeFormatterBuilder();
        dfBuilder.append(df1)
                 .appendLiteral(" hour: ")
                 .appendValue(ChronoField.HOUR_OF_DAY)
                 .appendLiteral(" minute: ")
                 .appendValue(ChronoField.MINUTE_OF_HOUR);
        DateTimeFormatter df2 = dfBuilder.toFormatter();
        
        // LocalDate, LocalDateTime to String
        System.out.println(df1.format(date1));
        System.out.println(df2.format(dateTime1));
        
        // String to LocalDate, LocalDateTime
        LocalDate date3 = LocalDate.parse("14 02 2017", df1);
        System.out.println(date3);
        LocalDateTime dateTime3 = LocalDateTime.parse("14 02 2017 hour: 0 minute: 0", df2);
        System.out.println(dateTime3);
    }
}
```

## String

```java

```

## StringJoiner