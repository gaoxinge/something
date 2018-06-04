import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Callable;
import java.util.List;
import java.util.ArrayList;

public class Main4 {
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
            Integer result = executor.invokeAny(tasks);
            System.out.println(result);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        executor.shutdown();
        while (!executor.isTerminated()) {}
        System.out.println("Finished all threads");
    }
}