/*
 * problem: the read do not block, the write block
 * plan1:   run callback in main loop
 * plan2:   run callback in method 
 */

import java.nio.ByteBuffer;
import java.nio.channels.Selector;
import java.nio.channels.SelectionKey;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.net.InetSocketAddress;
import java.io.IOException;
import java.util.Iterator;
import java.util.Set;


public class CallbackServer {
    public static void main( String[] args ) throws IOException {
        Selector selector = Selector.open();
        
        ServerSocketChannel serverChannel = ServerSocketChannel.open();
        serverChannel.socket().bind(new InetSocketAddress("127.0.0.1", 8080));
        serverChannel.configureBlocking(false);
        serverChannel.register(selector, SelectionKey.OP_ACCEPT);

        while (true) {
            selector.select();
            Iterator<SelectionKey> ite = selector.selectedKeys().iterator();

            while (ite.hasNext()) {
                SelectionKey key = ite.next();
                ite.remove();

                if (key.isAcceptable()) {
                    ServerSocketChannel s = (ServerSocketChannel) key.channel();
                    SocketChannel clientSocket = s.accept();
                    clientSocket.configureBlocking(false);
                    SelectionKey newKey = clientSocket.register(selector, SelectionKey.OP_WRITE);
                    newKey.attach(new CommonClient(clientSocket, newKey));
                } else if (key.isReadable()) {
                    CommonClient client = (CommonClient) key.attachment();
                    client.onRead();
                } else if (key.isWritable()) {
                    CommonClient client = (CommonClient) key.attachment();
                    client.onWrite();
                }
            }
        }
    }
}


class CommonClient {
    private SocketChannel clientSocket;
    private SelectionKey key;
    private ByteBuffer recvBuffer;
    private Callback callback;
    private String msg;


    public CommonClient(SocketChannel clientSocket, SelectionKey key) throws IOException {
        this.clientSocket = clientSocket;
        this.key = key;
        this.recvBuffer = ByteBuffer.allocate(8);

        this.clientSocket.configureBlocking(false);
    }

    private void sendMessage(String msg, Callback cback) {
        try {
            recvBuffer.clear();
            recvBuffer.put(msg.getBytes());
            recvBuffer.flip();
            clientSocket.write(recvBuffer);
            key.interestOps(SelectionKey.OP_READ);
            this.callback = cback;
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public void onRead() throws IOException {
        int res = 0;
        recvBuffer.clear();

        int n = clientSocket.read(recvBuffer);
        while (n == 0) {
            n = clientSocket.read(recvBuffer);
        }

        if (n == -1) {
            clientSocket.close();
            key.cancel();
            return;
        }
        
        recvBuffer.flip();
        
        int r = 0;
        while (recvBuffer.hasRemaining()) {
            r *= 10;
            r += recvBuffer.get() - '0';
        }
        
        this.callback.onSucceed(r);
        key.interestOps(SelectionKey.OP_READ);
    }

    public void onWrite() {
        sendMessage("divident", new Callback() {
            @Override
            public void onSucceed(int data) {
                int a = data;
                sendMessage("divisor", new Callback() {
                    @Override
                    public void onSucceed(int data) {
                        int b = data;
                        sendMessage(String.valueOf(a / b), null);
                    }
                });
            }
        });
    }
}


interface Callback {
    public void onSucceed(int data);
}