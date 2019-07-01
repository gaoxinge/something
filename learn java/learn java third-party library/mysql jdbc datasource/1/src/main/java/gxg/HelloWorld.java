package gxg;

import com.mysql.jdbc.jdbc2.optional.MysqlDataSource;
import javax.sql.DataSource;

import java.sql.Connection;
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class HelloWorld {
    public static void main(String[] args) throws SQLException {
        StringBuilder stringBuilder = new StringBuilder();
        String url = stringBuilder
                .append("jdbc:mysql://")
                .append(BasicInfo.HOST)
                .append(":")
                .append(BasicInfo.PORT)
                .append("/")
                .append(BasicInfo.DB)
                .toString();

        MysqlDataSource mysqlDataSource = new MysqlDataSource();
        mysqlDataSource.setUrl(url);
        mysqlDataSource.setUser(BasicInfo.USER);
        mysqlDataSource.setPassword(BasicInfo.PASSWORD);
        DataSource dataSource = mysqlDataSource;

        Connection connection = dataSource.getConnection();
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery(String.format("select count(*) from %s", BasicInfo.TABLE));
        while (resultSet.next())
            System.out.println(resultSet.getInt(1));
        statement.close();
        connection.close();
    }
}