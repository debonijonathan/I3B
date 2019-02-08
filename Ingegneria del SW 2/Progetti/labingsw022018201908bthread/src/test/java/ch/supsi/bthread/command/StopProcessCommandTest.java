package ch.supsi.bthread.command;

import ch.supsi.bthread.iface.ProcessManager;
import org.junit.Test;

import static org.junit.Assert.*;
import static org.mockito.Mockito.mock;

public class StopProcessCommandTest {

    @Test
    public void create() {
        ProcessManager pm = mock(ProcessManager.class);
        assertTrue(StopProcessCommand.create(pm) instanceof StopProcessCommand);
    }
}