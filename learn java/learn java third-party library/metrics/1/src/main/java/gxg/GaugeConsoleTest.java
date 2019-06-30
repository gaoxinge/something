package gxg;

import com.codahale.metrics.MetricRegistry;
import com.codahale.metrics.Gauge;
import com.codahale.metrics.ConsoleReporter;
import java.util.concurrent.TimeUnit;

public class GaugeConsoleTest {
    private static final MetricRegistry metricRegistry = new MetricRegistry();
    private static final Gauge<Integer> gauge_ = () -> 1;
    private static final Gauge gauge = metricRegistry.gauge("gauge", () -> gauge_);

    public static void main(String[] args) throws InterruptedException {
        ConsoleReporter consoleReporter = ConsoleReporter.forRegistry(metricRegistry).build();
        consoleReporter.start(1, TimeUnit.SECONDS);
        Thread.sleep(10000);
    }
}
