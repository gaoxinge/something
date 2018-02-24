package gxg;

import com.codahale.metrics.MetricRegistry;
import com.codahale.metrics.Gauge;
import com.codahale.metrics.Slf4jReporter;
import java.util.concurrent.TimeUnit;

public class GaugeSlf4jTest {
    private static final MetricRegistry metricRegistry = new MetricRegistry();
    private static final Gauge<Integer> gauge_ = () -> 1;
    private static final Gauge gauge = metricRegistry.gauge("gauge", () -> gauge_);

    public static void main(String[] args) throws InterruptedException {
        Slf4jReporter slf4jReporter = Slf4jReporter.forRegistry(metricRegistry).build();
        slf4jReporter.start(1, TimeUnit.SECONDS);
        Thread.sleep(10000);
    }
}
