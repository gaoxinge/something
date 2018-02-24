package gxg;

import com.codahale.metrics.MetricRegistry;
import com.codahale.metrics.Histogram;
import com.codahale.metrics.ConsoleReporter;
import java.util.concurrent.TimeUnit;

public class HistogramConsoleTest {
    private static final MetricRegistry metricRegistry = new MetricRegistry();
    private static final Histogram histogram = metricRegistry.histogram("histogram");

    public static void main(String[] args) throws InterruptedException {
        ConsoleReporter consoleReporter = ConsoleReporter.forRegistry(metricRegistry).build();
        consoleReporter.start(1, TimeUnit.SECONDS);
        histogram.update(1);
        histogram.update(2);
        histogram.update(3);
        Thread.sleep(10000);
    }
}
