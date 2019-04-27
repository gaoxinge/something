package gxg;
import com.google.gson.Gson;

public class HelloWorld {
    public static void main(String[] args) {
        User user = new User();
        user.setName("gxg");
        user.setAge(18);
        user.setEmailAddress("gxg@email.com");

        Gson gson = new Gson();

        System.out.println("User ---> String");
        String jsonString  = gson.toJson(user);
        System.out.println(jsonString);

        System.out.println("String ---> User");
        User u = gson.fromJson(jsonString, User.class);
        System.out.println(u.getName());
        System.out.println(u.getAge());
        System.out.println(u.getEmailAddress());
    }
}

class User {
    private String name;
    private Integer age;
    private String emailAddress;

    public void    setName(String name) {this.name = name;}
    public String  getName() {return this.name;}
    public void    setAge(Integer age) {this.age = age;}
    public Integer getAge() {return this.age;}
    public void    setEmailAddress(String emailAddress) {this.emailAddress = emailAddress;}
    public String  getEmailAddress() {return this.emailAddress;}
}