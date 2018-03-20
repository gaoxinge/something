package gxg;

import java.sql.*;

public class HelloWorld2 {
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

        Connection connection = DriverManager.getConnection(url, BasicInfo.USER, BasicInfo.PASSWORD);
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery(String.format("select count(*) from %s", BasicInfo.TABLE));
        while (resultSet.next())
            System.out.println(resultSet.getInt(1));
        statement.close();
        connection.close();
    }
}
