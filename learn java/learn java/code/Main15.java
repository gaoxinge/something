public class Main15 {
    
    public static void main(String[] args) throws Exception {
        Int I = new Int();
        I.setValue(0);
        
        Thread t1 = new Thread() {
            @Override
            public void run() {
                I.setValue(1);
                for (int i = 0; i < 5000; ++i) {
                    I.inc();
                }
                System.out.println(this.getName() + " " + I.getValue());
            }
        };
        
        Thread t2 = new Thread() {
            @Override
            public void run() {
                I.setValue(2);
                for (int i = 0; i < 5000; ++i) {
                    I.inc();
                }
                System.out.println(this.getName() + " " + I.getValue());
            }
        };
        
        t1.start();
        t2.start();
        t1.join();
        t2.join();
        
        System.out.println("Thread-main" + " " + I.getValue());
    }
}


class Int {
    private static final ThreadLocal<Integer> threadLocalI = new ThreadLocal<>();
    public void inc() {
        Integer i = threadLocalI.get();
        i += 1;
        threadLocalI.set(i);
    }
    public void setValue(Integer i) { threadLocalI.set(i); };
    public Integer getValue()       { return threadLocalI.get(); }
}