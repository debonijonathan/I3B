package ch.supsi.bthread.command;

import ch.supsi.bthread.controller.ExitController;
import org.junit.Test;

import static org.junit.Assert.*;
import static org.mockito.Mockito.mock;

public class ExitCommandTest {

    @Test
    public void create() {
        ExitController ec = mock(ExitController.class);
        assertTrue(ExitCommand.create(ec) instanceof ExitCommand);
    }
}