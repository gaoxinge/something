package gxg;

import gxg.utils.MysqlUtil;
import lombok.extern.slf4j.Slf4j;
import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;

@Slf4j
public class TestMysql {
    public static void main(String[] args) throws Exception {
        DataSource dataSource = MysqlUtil.getDataSource("");
        Connection connection = dataSource.getConnection();
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery("");
        while (resultSet.next())
            System.out.println(resultSet.getInt(1));
        statement.close();
        connection.close();
    }
}