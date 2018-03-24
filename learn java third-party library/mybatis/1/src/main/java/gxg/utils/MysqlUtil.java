package gxg.utils;

import gxg.mapper.DbMapper;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;
import org.apache.ibatis.session.Configuration;
import org.apache.ibatis.mapping.Environment;
import org.apache.ibatis.transaction.TransactionFactory;
import org.apache.ibatis.transaction.jdbc.JdbcTransactionFactory;
import com.alibaba.druid.pool.DruidDataSourceFactory;
import javax.sql.DataSource;
import java.util.Properties;
import java.util.concurrent.ConcurrentHashMap;

public class MysqlUtil {

    private static final String DRIVER   = "com.mysql.jdbc.Driver";
    private static final String HOST     = "";
    private static final String PORT     = "";
    private static final String USERNAME = "";
    private static final String PASSWORD = "";

    private static ConcurrentHashMap<String, SqlSessionFactory> sessionFactoryMap = new ConcurrentHashMap<>();

    public static SqlSessionFactory getSessionFactory(String dbName) throws Exception {
        if (sessionFactoryMap.containsKey(dbName)) return sessionFactoryMap.get(dbName);
        SqlSessionFactory sessionFactory = createSessionFactory(dbName);
        sessionFactoryMap.put(dbName, sessionFactory);
        return sessionFactory;
    }

    private static SqlSessionFactory createSessionFactory(String dbName) throws Exception {
        // properties
        Properties properties = new Properties();
        properties.put(DruidDataSourceFactory.PROP_DRIVERCLASSNAME, DRIVER);
        properties.put(DruidDataSourceFactory.PROP_URL, String.format("jdbc:mysql://%s:%s/%s", HOST, PORT, dbName));
        properties.put(DruidDataSourceFactory.PROP_USERNAME, USERNAME);
        properties.put(DruidDataSourceFactory.PROP_PASSWORD, PASSWORD);
        properties.put(DruidDataSourceFactory.PROP_VALIDATIONQUERY, "SELECT 1");
        properties.put(DruidDataSourceFactory.PROP_TESTWHILEIDLE, "true");
        properties.put(DruidDataSourceFactory.PROP_DEFAULTAUTOCOMMIT, "false");
        properties.put(DruidDataSourceFactory.PROP_TESTONBORROW, "false");
        properties.put(DruidDataSourceFactory.PROP_TIMEBETWEENEVICTIONRUNSMILLIS, "30000");
        properties.put(DruidDataSourceFactory.PROP_MINEVICTABLEIDLETIMEMILLIS, "15000");
        properties.put(DruidDataSourceFactory.PROP_DEFAULTTRANSACTIONISOLATION, "2");
        properties.put(DruidDataSourceFactory.PROP_MINIDLE, "1");

        // datasource
        DataSource dataSource = DruidDataSourceFactory.createDataSource(properties);

        // transaction
        TransactionFactory transactionFactory = new JdbcTransactionFactory();

        // environment
        Environment environment = new Environment("development", transactionFactory, dataSource);

        // configuration
        Configuration configuration = new Configuration(environment);
        configuration.addMapper(DbMapper.class);

        // session
        return new SqlSessionFactoryBuilder().build(configuration);
    }
}
