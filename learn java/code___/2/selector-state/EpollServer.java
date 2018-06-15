import java.nio.ByteBuffer;
import java.nio.channels.Selector;
import java.nio.channels.SelectionKey;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.net.InetSocketAddress;
import java.io.IOException;
import java.util.Iterator;
import java.util.Set;


public class EpollServer {
    public static void main(String[] args) throws IOException {
        Selector selector = Selector.open();
        
        ServerSocketChannel ssc = ServerSocketChannel.open();
        ssc.socket().bind(new InetSocketAddress("127.0.0.1", 8080));
        ssc.configureBlocking(false);
        ssc.register(selector, SelectionKey.OP_ACCEPT);

        ByteBuffer readBuff = ByteBuffer.allocate(1024);

        while (true) {
            int nReady = selector.select();
            Set<SelectionKey> keys = selector.selectedKeys();
            Iterator<SelectionKey> it = keys.iterator();

            while (it.hasNext()) {
                SelectionKey key = it.next();
                it.remove();

                if (key.isAcceptable()) {
                    SocketChannel socketChannel = ssc.accept();
                    socketChannel.configureBlocking(false);
                    SelectionKey connectionKey = socketChannel.register(selector, SelectionKey.OP_READ);
                    connectionKey.attach(new EpollTask(socketChannel, connectionKey));
                } else if (key.isReadable()) {
                    SocketChannel socketChannel = (SocketChannel) key.channel();
                    EpollTask conn = (EpollTask) key.attachment();
                    key.interestOps(SelectionKey.OP_WRITE);
                    
                    readBuff.clear();
                    socketChannel.read(readBuff);
                    readBuff.flip();
                    conn.onRead(getInt(readBuff));
                } else if (key.isWritable()) {
                    SocketChannel socketChannel = (SocketChannel) key.channel();
                    EpollTask conn = (EpollTask) key.attachment();
                    key.interestOps(SelectionKey.OP_READ);
                    
                    conn.onWrite();
                }
            }
        }
    }

    public static int getInt(ByteBuffer buf) {
        int r = 0;
        while (buf.hasRemaining()) {
            r *= 10;
            r += buf.get() - '0';
        }
        return r;
    }
}


class EpollTask {
    private SocketChannel socketChannel;
    private SelectionKey key;
    private ByteBuffer writeBuffer;
    
    private int state;
    private int dividend;
    private int divisor;
    private int result;
    
    public EpollTask(SocketChannel socketChannel, SelectionKey key) {
        this.socketChannel = socketChannel;
        this.key = key;
        this.writeBuffer = ByteBuffer.allocate(64);
    }

    public void onRead(int data) {
        if (state == 0) {
            dividend = data;
            System.out.println(dividend);
            state = 1;
        } else if (state == 2) {
            divisor = data;
            System.out.println(divisor);

            if (divisor == 0)
                result = Integer.MAX_VALUE;
            else
                result = dividend / divisor;
            
            state = 3;
        } else {
            throw new RuntimeException("wrong state " + state);
        }
    }

    public void onWrite() throws IOException {
        if (state == 1) {
            writeBuffer.clear();
            writeBuffer.put("divident".getBytes());
            writeBuffer.flip();
            socketChannel.write(writeBuffer);
            state = 2;
        } else if (state == 3) {
            writeBuffer.clear();
            writeBuffer.put(String.valueOf(result).getBytes());
            writeBuffer.flip();
            socketChannel.write(writeBuffer);
            socketChannel.close();
            key.cancel();
            state = 4;
        }
    }
}