package ch.supsi.bthread.view;

import org.junit.Test;

import static junit.framework.TestCase.assertTrue;

public class TableViewMutexFactoryTest {
    @Test
    public void instance(){
        assertTrue(TableViewMutexFactory.instance() instanceof TableViewMutexFactory);
    }
}
