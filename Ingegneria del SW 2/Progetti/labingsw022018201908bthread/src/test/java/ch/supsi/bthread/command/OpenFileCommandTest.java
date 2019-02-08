package ch.supsi.bthread.command;

import ch.supsi.bthread.mediator.MenuBarMediator;
import org.junit.Test;

import static org.junit.Assert.*;
import static org.mockito.Mockito.mock;

public class OpenFileCommandTest {

    @Test
    public void create() {
        MenuBarMediator mbm = mock(MenuBarMediator.class);
        assertTrue(OpenFileCommand.create(mbm) instanceof OpenFileCommand);
    }
}