import java.nio.ByteBuffer;
import java.nio.channels.Selector;
import java.nio.channels.SelectionKey;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.net.InetSocketAddress;
import java.io.IOException;
import java.util.Iterator;
import java.util.Set;

public class Server {
    public static void main(String[] args) throws IOException {
        Selector selector = Selector.open();

        ServerSocketChannel serverSocketChannel = ServerSocketChannel.open();
        serverSocketChannel.socket().bind(new InetSocketAddress("127.0.0.1", 8080));
        serverSocketChannel.configureBlocking(false);
        serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);

        ByteBuffer rb = ByteBuffer.allocate(1024);
        ByteBuffer wb = ByteBuffer.allocate(1024);

        while (true) {
            int readys = selector.select();
            if (readys == 0) continue;

            Set<SelectionKey> keys = selector.selectedKeys();
            Iterator<SelectionKey> it = keys.iterator();

            while (it.hasNext()) {
                SelectionKey key = it.next();
                it.remove();

                if (key.isAcceptable()) {
                    SocketChannel socketchannel = serverSocketChannel.accept();
                    socketchannel.configureBlocking(false);
                    socketchannel.register(selector, SelectionKey.OP_READ);
                } else if (key.isReadable()) {
                    SocketChannel socketChannel = (SocketChannel) key.channel();
                    socketChannel.register(selector, SelectionKey.OP_WRITE);

                    socketChannel.read(rb);
                    rb.flip();
                    System.out.print(new String(rb.array()));
                    System.out.println();
                    rb.clear();
                } else if (key.isWritable()) {
                    SocketChannel socketChannel = (SocketChannel) key.channel();
                    socketChannel.register(selector, SelectionKey.OP_READ);

                    wb.put("hello\n".getBytes());
                    wb.flip();
                    socketChannel.write(wb);
                    wb.clear();
                }
            }
        }
    }
}
