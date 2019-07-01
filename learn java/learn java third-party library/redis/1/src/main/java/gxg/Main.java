package gxg;

import redis.clients.jedis.Jedis;

public class Main {
    private static final String HOST = "127.0.0.1";
    private static final int PORT = 6379;

    public static void main(String[] args) {
        Jedis jedis = new Jedis(HOST, PORT);
        jedis.set("string-key", "string-value");
        System.out.println(jedis.get("string-key"));
    }
}
