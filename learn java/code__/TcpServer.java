import java.net.Socket;
import java.net.ServerSocket;

import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.IOException;

public class TcpServer {
    public static void main(String[] args) throws IOException {
        ServerSocket ss = new ServerSocket(8080);
        Socket conn = ss.accept();
        
        BufferedReader br = new BufferedReader(new InputStreamReader(conn.getInputStream()));
        String s = null;
        while ((s = br.readLine()) != null && !s.equals(""))
            System.out.println(s);

        br.close();
        conn.close();
        ss.close();
    }
}