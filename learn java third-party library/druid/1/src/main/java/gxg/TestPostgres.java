package gxg;

import gxg.utils.PostgresUtil;
import lombok.extern.slf4j.Slf4j;
import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.SQLException;

@Slf4j
public class TestPostgres {
    public static void main(String[] args) throws SQLException {
        DataSource dataSource = PostgresUtil.getDataSource("");
        Connection connection = dataSource.getConnection();
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery("");
        while (resultSet.next())
            System.out.println(resultSet.getInt(1));
        statement.close();
        connection.close();
    }
}