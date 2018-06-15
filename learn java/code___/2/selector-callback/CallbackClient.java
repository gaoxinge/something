import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.Random;


public class CallbackClient {
    public static void main(String[] args) throws IOException, InterruptedException {
        SocketChannel socketChannel = SocketChannel.open();
        socketChannel.connect(new InetSocketAddress("127.0.0.1", 8080));

        ByteBuffer writeBuffer = ByteBuffer.allocate(32);
        ByteBuffer readBuffer = ByteBuffer.allocate(32);

        getMessage(readBuffer, socketChannel);
        sendRandomInt(writeBuffer, socketChannel, 1000);
        getMessage(readBuffer, socketChannel);
        Thread.sleep(5000);
        sendRandomInt(writeBuffer, socketChannel, 10);
        getMessage(readBuffer, socketChannel);

        socketChannel.close();
    }

    public static void sendRandomInt(ByteBuffer writeBuffer, 
                                     SocketChannel socketChannel, 
                                     int bound) throws IOException {
        Random r = new Random();
        int d = r.nextInt(bound);
        if (d == 0) d = 1;
        System.out.println(d);
        
        writeBuffer.clear();
        writeBuffer.put(String.valueOf(d).getBytes());
        writeBuffer.flip();
        socketChannel.write(writeBuffer);
    }

    public static void getMessage(ByteBuffer readBuffer, 
                                  SocketChannel socketChannel) throws IOException {
        readBuffer.clear();
        socketChannel.read(readBuffer);
        readBuffer.flip();
        byte[] buf = new byte[16];
        readBuffer.get(buf, 0, readBuffer.remaining());
        System.out.println(new String(buf));
    }
}