# learn java

- [进击的Java新人](https://zhuanlan.zhihu.com/hinus)
- [content](https://zhuanlan.zhihu.com/p/24393775)

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

- preference: wrapper type > primitive type

```
+----------------+  wrapper +----------------+
|                |  ======> |                |
| primitive type |  autobox |  wrapper type  |
|                | <======  |                |
+----------------+          +----------------+
```

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