package gxg;

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.handler.ContextHandler;

public class Main {
    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);

        ContextHandler ctx = new ContextHandler();
        ctx.setContextPath("/path");
        ctx.setHandler(new SimpleHandler());

        server.setHandler(ctx);

        server.start();
        server.join();
    }
}
