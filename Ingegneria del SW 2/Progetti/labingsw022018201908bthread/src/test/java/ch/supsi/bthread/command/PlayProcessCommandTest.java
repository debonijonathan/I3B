package ch.supsi.bthread.command;

import ch.supsi.bthread.controller.ProcessController;
import ch.supsi.bthread.view.MyMenuItem;
import org.junit.Test;

import static org.junit.Assert.*;
import static org.mockito.Mockito.mock;

public class PlayProcessCommandTest {

    @Test
    public void create() {
        ProcessController pc = mock(ProcessController.class);
        assertTrue(PlayProcessCommand.create(pc) instanceof PlayProcessCommand);
    }

    @Test
    public void setPath() {
        ProcessController pc = mock(ProcessController.class);

        PlayProcessCommand ppc = PlayProcessCommand.create(pc);
        ppc.setPath("path");
        assertEquals("path", ppc.getPath());

    }
}