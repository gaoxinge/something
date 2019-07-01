package gxg.utils;

import com.alibaba.druid.pool.DruidDataSource;
import java.util.concurrent.ConcurrentHashMap;
import javax.sql.DataSource;

public class PostgresUtil {

    private static final String DRIVER           = "org.postgresql.Driver";
    private static final String HOST             = "";
    private static final String PORT             = "";
    private static final String USERNAME         = "";
    private static final String PASSWORD         = "";
    private static final Integer INITIAL_SIZE    = 1;
    private static final Integer MAX_ACTIVE      = 10;
    private static final Integer MIN_IDLE        = 5;
    private static final Boolean TEST_WHILE_IDLE = true;
    private static final String TEST_SQL         = "select 1";

    private static ConcurrentHashMap<String, DataSource> dataSourceMap = new ConcurrentHashMap<>();

    public static DataSource getDataSource(String dbName) {
        if (dataSourceMap.containsKey(dbName)) return dataSourceMap.get(dbName);
        DataSource dataSource = createDataSource(dbName);
        dataSourceMap.put(dbName, dataSource);
        return dataSource;
    }

    private static DataSource createDataSource(String dbName) {
        DruidDataSource dataSource = new DruidDataSource();
        dataSource.setDriverClassName(DRIVER);
        dataSource.setUrl(String.format("jdbc:postgresql://%s:%s/%s", HOST, PORT, dbName));
        dataSource.setUsername(USERNAME);
        dataSource.setPassword(PASSWORD);
        dataSource.setInitialSize(INITIAL_SIZE);
        dataSource.setMaxActive(MAX_ACTIVE);
        dataSource.setMinIdle(MIN_IDLE);
        dataSource.setTestWhileIdle(TEST_WHILE_IDLE);
        dataSource.setValidationQuery(TEST_SQL);
        return dataSource;
    }
}
