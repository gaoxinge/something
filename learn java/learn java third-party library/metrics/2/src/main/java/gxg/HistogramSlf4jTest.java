package gxg;

import com.codahale.metrics.MetricRegistry;
import com.codahale.metrics.Histogram;
import com.codahale.metrics.Slf4jReporter;
import java.util.concurrent.TimeUnit;

public class HistogramSlf4jTest {
    private static final MetricRegistry metricRegistry = new MetricRegistry();
    private static final Histogram histogram = metricRegistry.histogram("histogram");

    public static void main(String[] args) throws InterruptedException {
        Slf4jReporter slf4jReporter = Slf4jReporter.forRegistry(metricRegistry).build();
        slf4jReporter.start(1, TimeUnit.SECONDS);
        histogram.update(1);
        histogram.update(2);
        histogram.update(3);
        Thread.sleep(10000);
    }
}
