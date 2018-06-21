# spring in detail

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

### reference

- [Spring IOC有什么好处呢？](https://www.zhihu.com/question/23277575)
- [Spring整理系列(11)——@Configuration注解、@Bean注解以及配置自动扫描、bean作用域](http://blog.csdn.net/javaloveiphone/article/details/52182899)
- [Spring初探之bean工厂（上）](http://blog.csdn.net/windy83/article/details/7405032)
- [Spring初探之bean工厂（下）](http://blog.csdn.net/Windy83/article/details/7407546)
- [通过annotation(注解)实现BeanFactory工厂模式(三)](https://my.oschina.net/u/923324/blog/832269)

## AOP

### reference

- [什么是面向切面编程AOP？](https://www.zhihu.com/question/24863332)
- [为什么要用spring的IOC和AOP?用了IOC和AOP的优点缺点是什么?](https://www.zhihu.com/question/19993030)
- [SpringAOP基本用法(上)](https://zhuanlan.zhihu.com/p/25892085)
- [SpringAOP基本用法(中)](https://zhuanlan.zhihu.com/p/25892058)
- [SpringAOP基本用法(下)](https://zhuanlan.zhihu.com/p/25891989)
- [spring AOP是什么?你都拿它做什么?](https://zhuanlan.zhihu.com/p/28097563)