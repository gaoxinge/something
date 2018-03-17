# reflection and annotation

## reflection

### get class

```java
public class Test {
    public static void main(String[] args) {
        Class<?> demo1 = null;
        Class<?> demo2 = null;
        Class<?> demo3 = null;
        Class<?> demo4 = null;
        
        try {
            demo1=Class.forName("Demo");
        } catch(Exception e) {
            e.printStackTrace();
        }
        demo2 = (new Demo()).getClass();
        demo3 = new Demo().getClass();
        demo4 = Demo.class;
         
        System.out.println(demo1.getName());
        System.out.println(demo2.getName());
        System.out.println(demo3.getName());
        System.out.println(demo4.getName());
         
    }
}

class Demo{}
```

## getter and setter

```java
import java.lang.reflect.*;

public class Test {
    public static void main(String[] args) {
        Person person = new Person("man");
        System.out.println((String) person.get("Sex"));
        person.set("Sex", String.class, "woman");
        System.out.println((String) person.get("Sex"));
    }
}

class Person {
    
    private String sex;
    
    Person() {}
    
    Person(String sex) {
        this.sex = sex;
    }
    
    public String getSex() {
        return sex;
    }
    
    public void setSex(String sex) {
        this.sex = sex;
    }
    
    public Object get(String att) {
        try {
            Method method = Person.class.getMethod("get" + att);
            return method.invoke(this);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
    
    public void set(String att, Class<?> type, Object value) {
        try {
            Method method = Person.class.getMethod("set" + att, type);
            method.invoke(this, value);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

### decorator pattern

- standard

```java
public class Test {
    public static void main(String[] args) {
        Coffee coffee = new RealCoffee(10, "coffee");
        System.out.println(coffee.getPrice());
        System.out.println(coffee.getName());
        
        Coffee milkedCoffee = new MilkDecorator(coffee);
        System.out.println(milkedCoffee.getPrice());
        System.out.println(milkedCoffee.getName());
    }
}

interface Coffee {
    Integer getPrice();
    String getName();
}

class RealCoffee implements Coffee {
    
    private Integer price;
    private String name;
    
    RealCoffee(Integer price, String name) {
        this.price = price;
        this.name  = name;
    }
    
    @Override
    public Integer getPrice() {
        return price;
    }
    
    @Override
    public String getName() {
        return name;
    }
}

abstract class CoffeeDecorator implements Coffee {
    protected Coffee coffeeimpl;
    
    CoffeeDecorator(Coffee coffee) {
        this.coffeeimpl = coffee;
    }
    
    @Override
    public abstract Integer getPrice();
    
    @Override
    public abstract String getName();
}

class MilkDecorator extends CoffeeDecorator {
    
    MilkDecorator(Coffee coffee) {
        super(coffee);
    }
    
    @Override
    public Integer getPrice() {
        return coffeeimpl.getPrice() + 10;
    }
    
    @Override
    public String getName() {
        return "milked " + coffeeimpl.getName();
    }
}
```

- simplified

```java
public class Test {
    public static void main(String[] args) {
        Coffee coffee = new RealCoffee(10, "coffee");
        System.out.println(coffee.getPrice());
        System.out.println(coffee.getName());
        
        Coffee milkedCoffee = new MilkDecorator(coffee);
        System.out.println(milkedCoffee.getPrice());
        System.out.println(milkedCoffee.getName());
    }
}

interface Coffee {
    Integer getPrice();
    String getName();
}

class RealCoffee implements Coffee {
    
    private Integer price;
    private String name;
    
    RealCoffee(Integer price, String name) {
        this.price = price;
        this.name  = name;
    }
    
    @Override
    public Integer getPrice() {
        return price;
    }
    
    @Override
    public String getName() {
        return name;
    }
}

class MilkDecorator implements Coffee {
    protected Coffee coffeeimpl;
    
    MilkDecorator(Coffee coffee) {
        this.coffeeimpl = coffee;
    }
    
    @Override
    public Integer getPrice() {
        return coffeeimpl.getPrice() + 10;
    }
    
    @Override
    public String getName() {
        return "milked " + coffeeimpl.getName();
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
        Coffee coffee = new RealCoffee(10, "coffee");
        System.out.println(coffee.getPrice());
        System.out.println(coffee.getName());
        
        DecoratorHandler decorator = new DecoratorHandler();
        Coffee milkedCoffee = (Coffee) decorator.bind(coffee);
        System.out.println(milkedCoffee.getPrice());
        System.out.println(milkedCoffee.getName());
    }
}

interface Coffee {
    Integer getPrice();
    String getName();
}

class RealCoffee implements Coffee {
    
    private Integer price;
    private String name;
    
    RealCoffee(Integer price, String name) {
        this.price = price;
        this.name  = name;
    }
    
    @Override
    public Integer getPrice() {
        return price;
    }
    
    @Override
    public String getName() {
        return name;
    }
}

class DecoratorHandler implements InvocationHandler {
    private Object target;
    
    public Object bind(Object target) {
        this.target = target;
        return Proxy.newProxyInstance(
            target.getClass().getClassLoader(),
            target.getClass().getInterfaces(),
            this
        );
    }
    
    public Object invoke(Object decorator, Method method, Object[] args) throws Throwable {
        Object result = null;
        if (method.getName().equals("getPrice")) {
            Integer price = (Integer) method.invoke(target, args);
            result = price + 10;
        } else if (method.getName().equals("getName")) {
            String name = (String) method.invoke(target, args);
            result = "milked " + name;
        }
        return result;
    }
}
```

### static proxy

- standard

```java

```

- dynamical proxy

```java

```

### reference

- [java反射详解](https://www.cnblogs.com/rollenholt/archive/2011/09/02/2163758.html)
- [Java反射使用总结](http://www.cnblogs.com/zhaoyanjun/p/6074887.html)
- [Java动态代理作用是什么？](https://www.zhihu.com/question/20794107)
- [动态代理和静态代理的比较](https://www.jianshu.com/p/cf35dbec1988)

## annotation

### reference

- [Java注解](https://www.yiibai.com/java/java-annotation-tutorial.html)
- [Java注解教程：自定义注解示例，利用反射进行解析](http://www.importnew.com/14479.html)
- [框架开发之Java注解的妙用](http://www.importnew.com/23564.html)
- [Java注解指导手册–终极向导](http://www.importnew.com/14227.html)
- [深入理解Java：注解（Annotation）基本概念](http://www.cnblogs.com/peida/archive/2013/04/23/3036035.html)
- [深入理解Java：注解（Annotation）自定义注解入门](https://www.cnblogs.com/peida/archive/2013/04/24/3036689.html)
- [深入理解Java：注解（Annotation）注解处理器](http://www.cnblogs.com/peida/archive/2013/04/26/3038503.html)