package ch.supsi.bthread.view;

import org.junit.Test;

import static junit.framework.TestCase.assertTrue;

public class TableViewSemaphoreFactoryTest {
    @Test
    public void instance(){
        assertTrue(TableViewSemaphoreFactory.instance() instanceof TableViewSemaphoreFactory);
    }
}
