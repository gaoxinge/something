package gxg;

import com.codahale.metrics.MetricRegistry;
import com.codahale.metrics.Meter;
import com.codahale.metrics.Slf4jReporter;
import java.util.concurrent.TimeUnit;

public class MeterSlf4jTest {
    private static final MetricRegistry metricRegistry = new MetricRegistry();
    private static final Meter meter = metricRegistry.meter("meter");

    public static void main(String[] args) throws InterruptedException {
        Slf4jReporter slf4jReporter = Slf4jReporter.forRegistry(metricRegistry).build();
        slf4jReporter.start(1, TimeUnit.SECONDS);
        meter.mark(2);
        Thread.sleep(10000);
    }
}
