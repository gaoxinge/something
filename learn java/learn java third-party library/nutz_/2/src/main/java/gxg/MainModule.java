package gxg;

import org.nutz.mvc.annotation.*;

public class MainModule {

    @At("/hello")
    @Ok("jsp:/jsp/hello.jsp")
    public String doHello() {
        return "Hello Nutz";
    }
}