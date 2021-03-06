import java.util.Map;
import java.util.HashMap;

public class Main16 {
    public static void main(String[] args) throws Exception {
        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < 500; ++i) {
            map.put(i, i);
        }
        
        Thread t1 = new Thread() {
            @Override
            public void run() {
                Integer total = 0;
                for (Map.Entry<Integer, Integer> entry: map.entrySet()) {
                    total += 1;
                    System.out.println(getName() + " key: "+ entry.getKey() + " value: " + entry.getValue() + " ");
                }
                System.out.println(getName() + " total: " + total);
            }
        };
        
        Thread t2 = new Thread() {
            @Override
            public void run() {
                Integer total = 0;
                for (Map.Entry<Integer, Integer> entry: map.entrySet()) {
                    total += 1;
                    System.out.println(getName() + " key: " + entry.getKey() + " value: " + entry.getValue());
                }
                System.out.println(getName() + " total: " + total);
            }
        };
        
        t1.start();
        t2.start();
        t1.join();
        t2.join();
    }
}