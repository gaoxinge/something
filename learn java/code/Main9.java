public class Main9 {
    
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
    public void inc() { 
        synchronized (new Object()) {
            i += 1;
        }            
    }
    public int getInt() { return i; }
}