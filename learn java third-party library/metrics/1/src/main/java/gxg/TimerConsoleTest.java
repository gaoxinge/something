package gxg;

import com.codahale.metrics.MetricRegistry;
import com.codahale.metrics.Timer;
import com.codahale.metrics.ConsoleReporter;
import java.util.concurrent.TimeUnit;

public class TimerConsoleTest {
    private static final MetricRegistry metricRegistry = new MetricRegistry();
    private static final Timer timer = metricRegistry.timer("timer");

    public static Integer add(Integer a, Integer b) {
        Timer.Context context = timer.time();
        try {
            return a + b;
        } finally {
            context.stop();
        }
    }

    public static void main(String[] args) throws InterruptedException {
        ConsoleReporter consoleReporter = ConsoleReporter.forRegistry(metricRegistry).build();
        consoleReporter.start(1, TimeUnit.SECONDS);
        add(1, 1);
        add(1, 2);
        add(1, 3);
        Thread.sleep(10000);
    }
}
