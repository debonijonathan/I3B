package ch.supsi.bthread.command;

import ch.supsi.bthread.controller.MonitoringController;
import org.junit.Test;

import static org.junit.Assert.*;
import static org.mockito.Mockito.mock;

public class ExportCommandTest {

    @Test
    public void create() {
        MonitoringController mc = mock(MonitoringController.class);
        assertTrue(ExportCommand.create(mc) instanceof ExportCommand);
    }
}