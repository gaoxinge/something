import java.util.concurrent.locks.ReentrantLock;

public class Main14 {
    
    public static void main(String[] args) throws Exception {
        Int I = new Int();
        
        Thread t1 = new Thread() {
            @Override
            public void run() {
                for (int i = 0; i < 5000; ++i) {
                    I.inc();
                }
            }
        };
        
        Thread t2 = new Thread() {
            @Override
            public void run() {
                for (int i = 0; i < 5000; ++i) {
                    I.inc();
                }
            }
        };
        
        t1.start();
        t2.start();
        t1.join();
        t2.join();
        
        System.out.println(I.getInt());
    }
}


class Int {
    private int i = 0;
    private ReentrantLock lock = new ReentrantLock();
    public void inc() {
        lock.lock();
        i += 1; 
        lock.unlock();
    }
    public int getInt() { return i; }
}