import java.util.Arrays;

public class Main {
    private static double[] generate(int size) {
        double[] a = new double[size];
        for (int i = 0; i < size; i++) {
            a[i] = Math.random();
        }
        return a;
    }
    
    private static double[] TestSort(double[] a) {
        double[] b = Arrays.copyOf(a, a.length);
        long start = System.currentTimeMillis();
        Arrays.sort(b);
        long end = System.currentTimeMillis();
        System.out.println("[sort] size = " + b.length + ", time = " + (end - start));
        return b;
    }
    
    private static double[] TestParallelSort(double[] a) {
        double[] b = Arrays.copyOf(a, a.length);
        long start = System.currentTimeMillis();
        Arrays.parallelSort(b);
        long end = System.currentTimeMillis();
        System.out.println("[parallel sort] size = " + b.length + ", time = " + (end - start));
        return b;
    }
    
    private static void checkEqual(double x[], double y[], int size) {
        boolean bool = true;
        for (int i = 0; i < size; i++) {
            if (x[i] != y[i]) {
                bool = false;
            }
        }
        
        if (!bool) {
           System.out.println("x != y"); 
        }
    }
    
    public static void main(String[] args) {
        double[] a;
        double[] x;
        double[] y;
        
        int size = 10;
        while (size < 10000000) {
            a = generate(size);
            x = TestSort(a);
            y = TestParallelSort(a);
            checkEqual(x, y, size);
            size *= 2;
        }
    }
}