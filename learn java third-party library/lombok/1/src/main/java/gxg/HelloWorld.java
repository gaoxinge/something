package gxg;
import lombok.Data;
import lombok.NonNull;

public class HelloWorld {
    public static void main(String[] args) {
        User user = new User(1, "gxg");
        user.setPhone("151");
        System.out.println(user.getId());
        System.out.println(user.getName());
        System.out.println(user.getPhone());
        
        // pass null to constructor
        user = new User(1,    null);
        user = new User(null, "gxg"); // NullPointerException
    }
}

@Data
class User {
    private Integer id;
    private String name;
    private String phone;
    
    User(@NonNull Integer id, 
         String name) {
        this.id    = id;
        this.name  = name;
    }
}