package ch.supsi.bthread.view;
import org.junit.Test;
import static junit.framework.TestCase.assertTrue;

public class TableViewBarrierFactoryTest {
    @Test
    public void instance(){
        assertTrue(TableViewBarrierFactory.instance() instanceof TableViewBarrierFactory);
    }
}
