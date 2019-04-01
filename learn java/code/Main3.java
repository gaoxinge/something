import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.List;
import java.util.ArrayList;

public class Main3 {
    public static void main(String[] args) {
        ExecutorService executor = Executors.newFixedThreadPool(3);
        
        List<Integer> works = new ArrayList<>();
        for (int i = 0; i < 100; ++i) {
            works.add(i);
        }
        
        List<Runnable> tasks = new ArrayList<>();
        for (Integer work: works) {
            tasks.add(() -> System.out.println(work));
        }
        
        for (Runnable task: tasks) {
            executor.execute(task);
        }
        executor.shutdown();
        while (!executor.isTerminated()) {}
        System.out.println("Finished all threads");
    }
}