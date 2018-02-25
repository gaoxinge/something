package gxg;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;
import java.util.*;

public class HelloWorld {
    public static void main(String[] args) {
        Group group = new Group();
        group.setId(0L);
        group.setName("admin");

        User guestUser = new User();
        guestUser.setId(2L);
        guestUser.setName("guest");

        User rootUser = new User();
        rootUser.setId(3L);
        rootUser.setName("root");
        
        User nullUser = null;

        group.addUser(guestUser);
        group.addUser(rootUser);
        group.addUser(nullUser);
        
        // Group and String
        // serialization:   Group  ---> String
        // unserialization: String ---> Group
        System.out.println("=================================");
        String jsonString = JSON.toJSONString(group);
        System.out.println(jsonString);
        
        System.out.println("=================================");
        Group g = JSON.parseObject(jsonString, Group.class);
        System.out.println(g.getId());
        System.out.println(g.getName());
        System.out.println(g.getUsers());
        
        // String and JSONObject
        // unserialization: String     ---> JSONObject
        // serialization:   JSONObject ---> String
        System.out.println("=================================");
        JSONObject jsonObject = JSON.parseObject(jsonString);
        System.out.println(jsonObject.get("id"));
        System.out.println(jsonObject.get("name"));
        System.out.println(jsonObject.get("users"));
        
        System.out.println("=================================");
        String js = JSON.toJSONString(jsonObject);
        System.out.println(js);
    }
}

class Group {

    private Long       id;
    private String     name;
    private List<User> users = new ArrayList<User>();

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public List<User> getUsers() {
        return users;
    }

    public void setUsers(List<User> users) {
        this.users = users;
    }

    public void addUser(User user) {
        users.add(user);
    }
}

class User {

    private Long   id;
    private String name;

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}