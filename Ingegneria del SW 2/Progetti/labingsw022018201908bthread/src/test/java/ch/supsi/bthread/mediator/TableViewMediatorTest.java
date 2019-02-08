package ch.supsi.bthread.mediator;

import ch.supsi.bthread.model.Scheduler;
import org.junit.Test;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.assertTrue;
import static org.mockito.Mockito.mock;

public class TableViewMediatorTest {
    @Test
    public void create() {
        assertTrue(MenuBarMediator.create() instanceof MenuBarMediator);
    }

    @Test
    public void setTableViewMutex() {
        TableViewMediator tvm = TableViewMediator.create();
        tvm.setTableViewMutex(null);
        assertEquals(null, tvm.getTableViewMutex());
    }

    @Test
    public void setTableViewSamaphore() {
        TableViewMediator tvm = TableViewMediator.create();
        tvm.setTableViewSamaphore(null);
        assertEquals(null, tvm.getTableViewSamaphore());
    }

    @Test
    public void setTableViewBarrier() {
        TableViewMediator tvm = TableViewMediator.create();
        tvm.setTableViewBarrier(null);
        assertEquals(null, tvm.getTableViewBarrier());
    }

    @Test
    public void setTableViewCondVar() {
        TableViewMediator tvm = TableViewMediator.create();
        tvm.setTableViewCondVar(null);
        assertEquals(null, tvm.getTableViewCondVar());
    }

    @Test
    public void setTableViewThreadStatus() {
        TableViewMediator tvm = TableViewMediator.create();
        tvm.setTableViewThreadStatus(null);
        assertEquals(null, tvm.getTableViewThreadStatus());
    }

    @Test
    public void setScheduler() {
        Scheduler sc = mock(Scheduler.class);
        TableViewMediator tvm = TableViewMediator.create();
        tvm.setScheduler(sc);
        assertTrue(tvm.getScheduler() instanceof Scheduler);
    }

}
