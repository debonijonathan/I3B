package ch.supsi.bthread.controller;

import ch.supsi.bthread.iface.ExitManager;
import org.junit.Test;

import static org.junit.Assert.*;
import static org.mockito.Mockito.mock;

public class ExitControllerTest {

    @Test
    public void create() {
        ExitManager em = mock(ExitManager.class);
        assertTrue(ExitController.create(em) instanceof  ExitController);
    }
}