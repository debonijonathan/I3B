package ch.supsi.bthread.controller;

import ch.supsi.bthread.iface.MonitoringManager;
import org.junit.Test;

import static org.junit.Assert.*;
import static org.mockito.Mockito.mock;

public class MonitoringControllerTest {

    @Test
    public void create() {
        MonitoringManager mm = mock(MonitoringManager.class);
        assertTrue(MonitoringController.create(mm) instanceof  MonitoringController);
    }
}