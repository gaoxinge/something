import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Callable;
import java.util.concurrent.Future;
import java.util.List;
import java.util.ArrayList;

public class Main5 {
    public static void main(String[] args) {
        ExecutorService executor = Executors.newFixedThreadPool(3);
        
        List<Integer> works = new ArrayList<>();
        for (int i = 0; i < 100; ++i)
            works.add(i);
        
        List<Callable<Integer>> tasks = new ArrayList<>();
        for (Integer work: works) {
            tasks.add(() -> work);
        }
        
        try {
            List<Future<Integer>> results = executor.invokeAll(tasks);
            for (Future<Integer> result: results)
                System.out.println(result.get());
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        executor.shutdown();
        while (!executor.isTerminated()) {}
        System.out.println("Finished all threads");
    }
}