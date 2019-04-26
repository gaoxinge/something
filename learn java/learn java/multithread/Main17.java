import java.util.Map;
import java.util.HashMap;

public class Main17 {
    public static void main(String[] args) throws Exception {
        Map<Integer, Integer> map = new HashMap<>();
        
        Thread t1 = new Thread() {
            @Override
            public void run() {
                Integer total = 0;
                for (int i = 0; i < 500; ++i) {
                    if (i % 2 == 0) {
                        total += 1;
                        map.put(i, i);
                    }
                }
                System.out.println(getName() + " total: " + total + " size: " + map.size());
            }
        };
        
        Thread t2 = new Thread() {
            @Override
            public void run() {
                Integer total = 0;
                for (int i = 0; i < 500; ++i) {
                    if (i % 2 == 1) {
                        total += 1;
                        map.put(i, i);
                    }
                }
                System.out.println(getName() + " total: " + total + " size: " + map.size());
            }
        };
        
        t1.start();
        t2.start();
        t1.join();
        t2.join();
        
        System.out.println(map.size());
    }
}