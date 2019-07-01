package gxg;

public class Client {

    public static void main(String[] args) {
        Greeting greeting = new GreetingImpl();
        greeting.sayHello("Jack");
    }
}
