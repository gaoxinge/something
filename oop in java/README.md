# oop in java

## inheritance

### constructor

- subclass can not inherit base class's constructor
- if there is no keyword `super` in subclass, system will invoke the constructor without paramters in base class

```java
public class Test {
    public static void main(String[] args) {
        SubClass a = new SubClass(2); // error
    }
}

class SuperClass {
    private int n;
    
    // SuperClass() {}
    
    SuperClass(int n) {
        this.n = n;
    }
}

class SubClass extends SuperClass {
   private int n;
   
   SubClass(int n) {
       this.n = n;
   }
}
```

## polymorphism

- cast subclass to base class
  - can invoke subclass's method
  - can use `instanceof` to check
  - can cast to original class

```java
public class Test {
    public static void main(String[] args) {
        Animal a = new Cat(); 
        a.eat();
        Cat c = (Cat) a;
        c.eat();
        
        show(new Cat());
        show(new Dog());
        show(new Animal());
    }
            
    public static void show(Animal a) {
        a.eat();
        if (a instanceof Cat) {
            Cat c = (Cat) a;  
            c.work();
        } else if (a instanceof Dog) {
            Dog c = (Dog) a;  
            c.work();
        }
    }
}
 
class Animal {  
    public void eat() {
        System.out.println("eat something");
    }

    public void work() {
        System.out.println("get something");
    }
}  
  
class Cat extends Animal {
    @Override
    public void eat() { 
        System.out.println("eat fish");  
    }
    
    @Override
    public void work() {
        System.out.println("get fish");  
    }  
}  
  
class Dog extends Animal {
    @Override
    public void eat() {  
        System.out.println("eat meat");  
    }
    
    @Override
    public void work() {  
        System.out.println("get meat");  
    }  
}
```