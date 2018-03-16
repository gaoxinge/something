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

### reference

- [java反射详解](https://www.cnblogs.com/rollenholt/archive/2011/09/02/2163758.html)
- [Java反射使用总结](http://www.cnblogs.com/zhaoyanjun/p/6074887.html)

## annotation

### reference

- [Java注解](https://www.yiibai.com/java/java-annotation-tutorial.html)
- [Java注解教程：自定义注解示例，利用反射进行解析](http://www.importnew.com/14479.html)
- [框架开发之Java注解的妙用](http://www.importnew.com/23564.html)
- [Java注解指导手册–终极向导](http://www.importnew.com/14227.html)
- [深入理解Java：注解（Annotation）基本概念](http://www.cnblogs.com/peida/archive/2013/04/23/3036035.html)
- [深入理解Java：注解（Annotation）自定义注解入门](https://www.cnblogs.com/peida/archive/2013/04/24/3036689.html)
- [深入理解Java：注解（Annotation）注解处理器](http://www.cnblogs.com/peida/archive/2013/04/26/3038503.html)