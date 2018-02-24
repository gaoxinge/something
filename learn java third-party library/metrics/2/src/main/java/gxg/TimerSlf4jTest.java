package gxg;

import com.codahale.metrics.MetricRegistry;
import com.codahale.metrics.Timer;
import com.codahale.metrics.Slf4jReporter;
import java.util.concurrent.TimeUnit;

public class TimerSlf4jTest {
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
        Slf4jReporter slf4jReporter = Slf4jReporter.forRegistry(metricRegistry).build();
        slf4jReporter.start(1, TimeUnit.SECONDS);
        add(1, 1);
        add(1, 2);
        add(1, 3);
        Thread.sleep(10000);
    }
}
