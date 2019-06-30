package gxg;

import org.junit.Assert;
import org.junit.Test;
import static org.mockito.Mockito.*;

import java.util.List;

public class SimpleTest {

    @Test
    public void simpleTest() {
        List<String> list = mock(List.class);
        when(list.get(0)).thenReturn("helloworld"); // set excepted value

        String result = list.get(0);
        verify(list).get(0);                        // verify list invoke get(0) once
        result = list.get(0);
        verify(list, times(2)).get(0);              // verify list invoke get(0) twice
        Assert.assertEquals("helloworld", result);
    }
}
