import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.Random;


public class EpollClient {
    public static void main(String[] args) throws IOException, InterruptedException {
        SocketChannel socketChannel = SocketChannel.open();
        socketChannel.connect(new InetSocketAddress("127.0.0.1", 8080));

        ByteBuffer writeBuffer = ByteBuffer.allocate(32);
        ByteBuffer readBuffer = ByteBuffer.allocate(32);
        
        int d = 0;
        Random r = new Random();
        
        d = r.nextInt(1000);
        System.out.println(d);
        writeBuffer.clear();
        writeBuffer.put(String.valueOf(d).getBytes());
        writeBuffer.flip();
        socketChannel.write(writeBuffer);

        readBuffer.clear();
        socketChannel.read(readBuffer);
        readBuffer.flip();
        System.out.println(new String(readBuffer.array()));

        Thread.sleep(5000);

        d = r.nextInt(10);
        System.out.println(d);
        writeBuffer.clear();
        writeBuffer.put(String.valueOf(d).getBytes());
        writeBuffer.flip();
        socketChannel.write(writeBuffer);

        readBuffer.clear();
        socketChannel.read(readBuffer);
        readBuffer.flip();
        byte[] buf = new byte[32];
        readBuffer.get(buf, 0, readBuffer.remaining());
        System.out.println(new String(buf));

        socketChannel.close();
    }
}