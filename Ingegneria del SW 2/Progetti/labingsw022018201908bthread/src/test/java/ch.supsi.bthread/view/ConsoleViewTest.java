package ch.supsi.bthread.view;

import org.junit.Test;

import static junit.framework.TestCase.assertNull;

public class ConsoleViewTest {
    @Test
    public void getActualComponent(){
        assertNull(new ConsoleView().getActualComponent());
    }
}
