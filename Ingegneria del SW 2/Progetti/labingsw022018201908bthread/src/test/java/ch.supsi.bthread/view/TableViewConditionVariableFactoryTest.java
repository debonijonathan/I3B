package ch.supsi.bthread.view;

import org.junit.Test;

import static junit.framework.TestCase.assertTrue;

public class TableViewConditionVariableFactoryTest {
    @Test
    public void instance(){
        assertTrue(TableViewConditionVariableFactory.instance() instanceof TableViewConditionVariableFactory);
    }
}
