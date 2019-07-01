## content

## big picture

### spring

- spring framework: xml config
- spring boot: annotation config
- spring cloud
- spring cloud data flow

### reference

- [Spring框架简介](https://www.ibm.com/developerworks/cn/java/wa-spring1/)
- [Spring框架学习](http://blog.csdn.net/lishuangzhe7047/article/details/20740209)
- [Spring教程](http://wiki.jikexueyuan.com/project/spring/)
- [Spring教程|易百教程](http://www.yiibai.com/spring/)

## spring container

### annotation

- @Configuration
- @EnableAutoConfiguration
- @ComponentScan
- @SpringBootApplication = @Configuration + @EnableAutoConfiguration + @ComponentScan

## IOC/DI

### bean factory

- factory pattern
- singleton
- prototype

### put into bean factory

- class
  - @Component
  - @Controller: Action
  - @Service: Service
  - @Repository: Dao
- method
  - @Configuration
  - @Bean
  
### get from bean factory

- @Autowired
- @Resource
- @Injected

### example

- standard

```java
public class Test {
    public static void main(String[] args) {
        Apple apple = (Apple) FruitFactory.getInstance("Apple");
        apple.eat();
        
        Orange orange = (Orange) FruitFactory.getInstance("Orange");
        orange.eat();
    }
}

interface Fruit {
    void eat();
}

class Apple implements Fruit {
    @Override
    public void eat() {
        System.out.println("eat an apple");
    }
}

class Orange implements Fruit {
    @Override
    public void eat() {
        System.out.println("eat an orange");
    }
}

class FruitFactory {
    public static Fruit getInstance(String fruitName) {
        Fruit fruit = null;
        if ("Apple".equals(fruitName)) {
            fruit = new Apple();
        } else if ("Orange".equals(fruitName)) {
            fruit = new Orange();
        }
        return fruit;
    }
}
```

- reflection

```java
public class Test {
    public static void main(String[] args) {
        Apple apple = (Apple) FruitFactory.getInstance("Apple");
        apple.eat();
        
        Orange orange = (Orange) FruitFactory.getInstance("Orange");
        orange.eat();
    }
}

interface Fruit {
    void eat();
}

class Apple implements Fruit {
    @Override
    public void eat() {
        System.out.println("eat an apple");
    }
}

class Orange implements Fruit {
    @Override
    public void eat() {
        System.out.println("eat an orange");
    }
}

class FruitFactory {
    public static Fruit getInstance(String fruitName) {
        Fruit fruit = null;
        try {
            fruit = (Fruit) Class.forName(fruitName).newInstance();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return fruit;
    }
}
```

### spring ioc/di

- [1](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java%20third-party%20library/spring_/spring%20ioc%20di/1)
- [2](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java%20third-party%20library/spring_/spring%20ioc%20di/2)
- [3](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java%20third-party%20library/spring_/spring%20ioc%20di/3)

### reference

- [Spring IOC有什么好处呢？](https://www.zhihu.com/question/23277575)
- [Spring整理系列(11)——@Configuration注解、@Bean注解以及配置自动扫描、bean作用域](http://blog.csdn.net/javaloveiphone/article/details/52182899)
- [Spring初探之bean工厂（上）](http://blog.csdn.net/windy83/article/details/7405032)
- [Spring初探之bean工厂（下）](http://blog.csdn.net/Windy83/article/details/7407546)
- [通过annotation(注解)实现BeanFactory工厂模式(三)](https://my.oschina.net/u/923324/blog/832269)

## AOP

### example

- standard

```java
public class Test {
    public static void main(String[] args) {
        Subject sub = new SubjectProxy();
        sub.doSomething();
    }
}

interface Subject {
    void doSomething();
}

class RealSubject implements Subject {
    @Override
    public void doSomething() {
        System.out.println("call doSomethong()");
    }
}

class SubjectProxy implements Subject {
    Subject subimpl = new RealSubject();
    
    @Override
    public void doSomething() {
        subimpl.doSomething();
    }
}
```

- dynamical proxy

```java
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

public class Test {
    public static void main(String[] args) {
       ProxyHandler proxy = new ProxyHandler();
       Subject sub = (Subject) proxy.bind(new RealSubject());
       sub.doSomething();
    }
}

interface Subject {
    void doSomething();
}

class RealSubject implements Subject {
    @Override
    public void doSomething() {
        System.out.println("call doSomethong()");
    }
}

class ProxyHandler implements InvocationHandler {
    private Object tar;
    
    public Object bind(Object tar) {
        this.tar = tar;
        return Proxy.newProxyInstance(
            tar.getClass().getClassLoader(),
            tar.getClass().getInterfaces(),
            this
        );
    }
    
    public Object invoke(Object decorator, Method method, Object[] args) throws Throwable {
        Object result = null;
        result = method.invoke(tar, args);
        return result;
    }
}
```

### spring aop

- [1](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java%20third-party%20library/spring_/spring%20aop/1)

### spring aspectj

- [1](https://github.com/gaoxinge/something/tree/master/learn%20java/learn%20java%20third-party%20library/spring_/spring%20aspectj/1)

### reference

- [什么是面向切面编程AOP？](https://www.zhihu.com/question/24863332)
- [为什么要用spring的IOC和AOP?用了IOC和AOP的优点缺点是什么?](https://www.zhihu.com/question/19993030)
- [SpringAOP基本用法(上)](https://zhuanlan.zhihu.com/p/25892085)
- [SpringAOP基本用法(中)](https://zhuanlan.zhihu.com/p/25892058)
- [SpringAOP基本用法(下)](https://zhuanlan.zhihu.com/p/25891989)
- [spring AOP是什么?你都拿它做什么?](https://zhuanlan.zhihu.com/p/28097563)
- [AOP那点事儿](https://my.oschina.net/huangyong/blog/161338)
- [AOP那点事儿（续集）](https://my.oschina.net/huangyong/blog/161402)
- [Defining pointcuts by annotations](https://blog.jayway.com/2015/09/08/defining-pointcuts-by-annotations/)
- [在Gradle项目中配置AspectJ](http://chaosleong.github.io/2017/09/22/Configure-AspectJ-in-Gradle-project/)
- [IntelliJ IDEA + AspectJ](https://stackoverflow.com/questions/44088421/intellij-idea-aspectj)