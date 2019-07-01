package gxg;

import java.sql.DriverManager;
import java.sql.Connection;
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class HelloWorld {
    public static void main(String[] args) {
        try {
            StringBuilder stringBuilder = new StringBuilder();
            String url = stringBuilder
                    .append("jdbc:mysql://")
                    .append(BasicInfo.HOST)
                    .append(":")
                    .append(BasicInfo.PORT)
                    .append("/")
                    .append(BasicInfo.DB)
                    .append("?user=")
                    .append(BasicInfo.USER)
                    .append("&password=")
                    .append(BasicInfo.PASSWORD)
                    .toString();

            Connection connection = DriverManager.getConnection(url);
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery(String.format("select count(*) from %s", BasicInfo.TABLE));
            while (resultSet.next())
                System.out.println(resultSet.getInt(1));
            statement.close();
            connection.close();
        } catch (SQLException e) {
            System.out.println("error: " + e.toString() + " message: " + e.getMessage());
        }
    }
}