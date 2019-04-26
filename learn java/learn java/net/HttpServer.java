import java.net.Socket;
import java.net.ServerSocket;

import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;

public class HttpServer {
    public static void main(String[] args) throws IOException {
        ServerSocket ss = new ServerSocket(8080);
        Socket conn = ss.accept();
        
        BufferedReader br = new BufferedReader(new InputStreamReader(conn.getInputStream()));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(conn.getOutputStream()));

        String s = null;
        while ((s = br.readLine()) != null && !s.equals(""))
            System.out.println(s);

            
        bw.write("HTTP/1.1 200 OK\n");
        bw.write("Content-Type: text/html; charset=UTF-8\n\n");
        bw.write("<html>\n" +
                 "<head>\n" +
                 "<title>first page</title>\n" +
                 "</head>\n" +
                 "<body>\n" +
                 "<h1>Hello World!</h1>\n" +
                 "</body>\n" +
                 "</html>\n");
        bw.flush();

        br.close();
        bw.close();
        conn.close();
        ss.close();
    }
}