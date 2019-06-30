package gxg;

import com.codahale.metrics.MetricRegistry;
import com.codahale.metrics.Counter;
import com.codahale.metrics.ConsoleReporter;
import java.util.concurrent.TimeUnit;

public class CounterConsoleTest {
    private static final MetricRegistry metricRegistry = new MetricRegistry();
    private static final Counter counter = metricRegistry.counter("conuter");
    
    public static void main(String[] args) throws InterruptedException {
        ConsoleReporter consoleReporter = ConsoleReporter.forRegistry(metricRegistry).build();
        consoleReporter.start(1, TimeUnit.SECONDS);
        counter.inc();
        Thread.sleep(10000);
    }
}
