package ch.supsi.bthread.mediator;

import ch.supsi.bthread.command.PlayProcessCommand;
import ch.supsi.bthread.view.MyMenuItem;
import org.junit.Test;

import static junit.framework.TestCase.assertTrue;
import static org.mockito.Mockito.mock;

public class MenuBarMediatorTest {
    @Test
    public void create() {
        assertTrue(MenuBarMediator.create() instanceof MenuBarMediator);
    }

    @Test
    public void setPlayMenuItem() {
        MyMenuItem mi = mock(MyMenuItem.class);
        MenuBarMediator mbm = MenuBarMediator.create();
        mbm.setPlayMenuItem(mi);
        assertTrue(mbm.getPlayMenuItem() instanceof MyMenuItem);
    }

    @Test
    public void setStopMenuItem() {
        MyMenuItem mi = mock(MyMenuItem.class);
        MenuBarMediator mbm = MenuBarMediator.create();
        mbm.setStopMenuItem(mi);
        assertTrue(mbm.getStopMenuItem() instanceof MyMenuItem);
    }

    @Test
    public void setPauseMenuItem() {
        MyMenuItem mi = mock(MyMenuItem.class);
        MenuBarMediator mbm = MenuBarMediator.create();
        mbm.setPauseMenuItem(mi);
        assertTrue(mbm.getPauseMenuItem() instanceof MyMenuItem);
    }

    @Test
    public void setPlayProcessCommand() {
        PlayProcessCommand ppc = mock(PlayProcessCommand.class);
        MenuBarMediator mbm = MenuBarMediator.create();
        mbm.setPlayProcessCommand(ppc);
        assertTrue(mbm.getPlayProcessCommand() instanceof PlayProcessCommand);
    }

}
