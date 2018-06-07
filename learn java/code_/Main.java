enum Singleton {
    INSTANCE;
    
    private String name;
    public String getName() {return name;}
    public void setName(String name) {this.name = name;}
    
    public void sayHello() {
        System.out.println("hello");
    }
}


public class Main {
    public static void main(String[] args) {
        Singleton instance = Singleton.INSTANCE;
        
        instance.setName("gxg");
        System.out.println(instance.getName());
        
        instance.sayHello();
    }
}