package gxg.utils;

import com.alibaba.druid.pool.DruidDataSourceFactory;
import java.util.concurrent.ConcurrentHashMap;
import java.util.Properties;
import javax.sql.DataSource;

public class MysqlUtil {

    private static final String DRIVER    = "com.mysql.jdbc.Driver";
    private static final String HOST      = "";
    private static final String PORT      = "";
    private static final String USERNAME  = "";
    private static final String PASSWORD  = "";

    private static ConcurrentHashMap<String, DataSource> dataSourceMap = new ConcurrentHashMap<>();

    public static DataSource getDataSource(String dbName) throws Exception {
        if (dataSourceMap.containsKey(dbName)) return dataSourceMap.get(dbName);
        DataSource dataSource = createDataSource(dbName);
        dataSourceMap.put(dbName, dataSource);
        return dataSource;
    }

    private static DataSource createDataSource(String dbName) throws Exception {
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
        return DruidDataSourceFactory.createDataSource(properties);
    }
}
