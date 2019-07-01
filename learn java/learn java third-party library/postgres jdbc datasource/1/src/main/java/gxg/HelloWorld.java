package gxg;

import org.postgresql.ds.PGSimpleDataSource;
import javax.sql.DataSource;

import java.sql.Connection;
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class HelloWorld {
    public static void main(String[] args) throws SQLException {
        StringBuilder stringBuilder = new StringBuilder();
        String url = stringBuilder
                .append("jdbc:postgresql://")
                .append(BasicInfo.HOST)
                .append(":")
                .append(BasicInfo.PORT)
                .append("/")
                .append(BasicInfo.DB)
                .append("?stringtype=unspecified")
                .toString();

        PGSimpleDataSource pgSimpleDataSource = new PGSimpleDataSource();
        pgSimpleDataSource.setUrl(url);
        pgSimpleDataSource.setUser(BasicInfo.USER);
        pgSimpleDataSource.setPassword(BasicInfo.PASSWORD);
        DataSource dataSource = pgSimpleDataSource;

        Connection connection = dataSource.getConnection();
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery(String.format("select count(*) from %s", BasicInfo.TABLE));
        while (resultSet.next())
            System.out.println(resultSet.getInt(1));
        statement.close();
        connection.close();
    }
}