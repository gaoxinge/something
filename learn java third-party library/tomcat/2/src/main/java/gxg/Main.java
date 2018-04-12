package gxg;

import org.apache.catalina.LifecycleException;
import org.apache.catalina.startup.Tomcat;
import javax.servlet.ServletException;
import java.io.File;

public class Main {
    public static void main(String[] args) throws LifecycleException, InterruptedException, ServletException {
        Tomcat tomcat = new Tomcat();
        tomcat.setPort(8080);
        tomcat.addWebapp("/", new File("src/main/webapp/").getAbsolutePath());
        tomcat.start();
        tomcat.getServer().await();
    }
}
