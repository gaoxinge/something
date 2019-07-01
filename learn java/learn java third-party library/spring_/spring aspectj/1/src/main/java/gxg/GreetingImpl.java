package gxg;


public class GreetingImpl implements Greeting {

    @Tag
    @Override
    public void sayHello(String name) {
        System.out.println("Hello! " + name);
    }
}
