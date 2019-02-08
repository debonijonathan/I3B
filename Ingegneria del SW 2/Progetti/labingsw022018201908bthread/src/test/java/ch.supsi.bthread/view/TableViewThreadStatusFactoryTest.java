package ch.supsi.bthread.view;

import org.junit.Test;

import static junit.framework.TestCase.assertTrue;

public class TableViewThreadStatusFactoryTest {
    @Test
    public void instance(){
        assertTrue(TableViewThreadStatusFactory.instance() instanceof TableViewThreadStatusFactory);
    }
}
