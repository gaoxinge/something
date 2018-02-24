package gxg;

import com.codahale.metrics.MetricRegistry;
import com.codahale.metrics.Counter;
import com.codahale.metrics.Slf4jReporter;
import java.util.concurrent.TimeUnit;

public class CounterSlf4jTest {
    private static final MetricRegistry metricRegistry = new MetricRegistry();
    private static final Counter counter = metricRegistry.counter("conuter");
    
    public static void main(String[] args) throws InterruptedException {
        Slf4jReporter slf4jReporter = Slf4jReporter.forRegistry(metricRegistry).build();
        slf4jReporter.start(1, TimeUnit.SECONDS);
        counter.inc();
        Thread.sleep(10000);
    }
}
