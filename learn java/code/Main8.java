public class Main8 {
    
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
    private Object o = new Object();
    public void inc() { 
        synchronized (o) {   // only one thread get the block at some time (refer to same Int Object)
            i += 1;
        }            
    }
    public int getInt() { return i; }
}