import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.List;
import java.util.Arrays;
import java.util.ArrayList;

public class Main3 {
    public static void main(String[] args) {
        ExecutorService executor = Executors.newFixedThreadPool(3);
        List<Integer> works = new ArrayList<>();
        for (int i = 0; i < 1000000; ++i) {
            works.add(i);
        }
        for (Integer work: works) {
            executor.execute(() -> System.out.println(work));
        }
        executor.shutdown();
        while (!executor.isTerminated()) {}
        System.out.println("Finished all threads");
    }
}