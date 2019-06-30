package gxg;

import org.junit.Test;

import java.util.List;

import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

public class ComplexTest {

    @Test
    public void simpleTest() {
        List<String> list = mock(List.class);
        when(list.get(0)).thenReturn("helloworld");
        list.add("helloworld");
        System.out.println(list.get(0));  // helloworld
        System.out.println(list.get(1));  // null
    }
}
