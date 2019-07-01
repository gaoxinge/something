package gxg.utils;

import gxg.pojo.DbInfo;
import org.hibernate.cfg.Environment;
import org.hibernate.cfg.Configuration;
import org.hibernate.SessionFactory;

public class MysqlUtil {

    private static final String DATA_SOURCE = "com.alibaba.druid.support.hibernate.DruidConnectionProvider";
    private static final String DRIVER      = "com.mysql.jdbc.Driver";
    private static final String HOST        = "";
    private static final String PORT        = "";
    private static final String USERNAME    = "";
    private static final String PASSWORD    = "";
    private static final String DB_NAME     = "mysql";

    private static SessionFactory sessionFactory;

    public static void initDefaultSessionFactory() {
        Configuration configuration = new Configuration()
                .setProperty(Environment.DRIVER, DRIVER)
                .setProperty(Environment.URL, String.format("jdbc:mysql://%s:%s/%s", HOST, PORT, DB_NAME))
                .setProperty(Environment.USER, USERNAME)
                .setProperty(Environment.PASS, PASSWORD)
                .setProperty(Environment.DIALECT, "org.hibernate.dialect.H2Dialect")
                .setProperty(Environment.SHOW_SQL, "true")
                .addAnnotatedClass(DbInfo.class);
        sessionFactory = configuration.buildSessionFactory();
    }

    public static void initDruidSessionFactory() {
        Configuration configuration = new Configuration()
                .setProperty(Environment.CONNECTION_PROVIDER, DATA_SOURCE)
                .setProperty("driverClassName", DRIVER)
                .setProperty("url", String.format("jdbc:mysql://%s:%s/%s", HOST, PORT, DB_NAME))
                .setProperty("username", USERNAME)
                .setProperty("password", PASSWORD)
                .setProperty(Environment.DIALECT, "org.hibernate.dialect.H2Dialect")
                .setProperty(Environment.SHOW_SQL, "true")
                .addAnnotatedClass(DbInfo.class);
        sessionFactory = configuration.buildSessionFactory();
    }

    public static SessionFactory getSessionFactory() {
        return sessionFactory;
    }
}
