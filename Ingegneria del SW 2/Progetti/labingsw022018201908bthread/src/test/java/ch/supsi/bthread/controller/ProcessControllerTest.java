package ch.supsi.bthread.controller;

import ch.supsi.bthread.iface.ProcessManager;
import org.junit.Test;

import static org.junit.Assert.*;
import static org.mockito.Mockito.mock;

public class ProcessControllerTest {

    @Test
    public void create() {
        ProcessManager pm = mock(ProcessManager.class);
        assertTrue(ProcessController.create(pm) instanceof  ProcessController);
    }
}