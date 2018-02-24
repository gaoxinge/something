package gxg;

import com.codahale.metrics.MetricRegistry;
import com.codahale.metrics.Meter;
import com.codahale.metrics.ConsoleReporter;
import java.util.concurrent.TimeUnit;

public class MeterConsoleTest {
    private static final MetricRegistry metricRegistry = new MetricRegistry();
    private static final Meter meter = metricRegistry.meter("meter");

    public static void main(String[] args) throws InterruptedException {
        ConsoleReporter consoleReporter = ConsoleReporter.forRegistry(metricRegistry).build();
        consoleReporter.start(1, TimeUnit.SECONDS);
        meter.mark(2);
        Thread.sleep(10000);
    }
}
