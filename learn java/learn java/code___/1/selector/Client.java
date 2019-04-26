import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.net.InetSocketAddress;
import java.io.IOException;

public class Client {
    public static void main(String[] args) throws IOException {
        SocketChannel socketChannel = SocketChannel.open();
        socketChannel.connect(new InetSocketAddress("127.0.0.1", 8080));
        
        ByteBuffer rb = ByteBuffer.allocate(1024);
        ByteBuffer wb = ByteBuffer.allocate(1024);
            

        while (true) {
            wb.put("hello\n".getBytes());
            wb.flip();
            socketChannel.write(wb);
            wb.clear();
            
            socketChannel.read(rb);
            rb.flip();
            System.out.print(new String(rb.array()));
            System.out.println();
            rb.clear();
        }
    }
}