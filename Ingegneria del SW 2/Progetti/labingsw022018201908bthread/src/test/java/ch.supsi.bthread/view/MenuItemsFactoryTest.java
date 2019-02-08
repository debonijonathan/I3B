package ch.supsi.bthread.view;

import ch.supsi.bthread.iface.Command;
import javafx.embed.swing.JFXPanel;
import org.junit.Before;
import org.junit.Ignore;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mockito;

import static junit.framework.TestCase.assertTrue;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

//@RunWith(JfxRunner.class)
public class MenuItemsFactoryTest {

    @Before
    public  void initContext(){
        new JFXPanel();
    }

    @Test
    public void instanceTest(){
        assertTrue(MenuItemsFactory.instance() instanceof MenuItemsFactory);
    }

    @Test
    public void createTracingMenuItemTest(){
        Command cmd = mock(Command.class);
        assertTrue(MenuItemsFactory.instance().createTracingMenuItem(cmd) instanceof MyMenuItem);
    }

    @Test
    public void createOpenMenuItemTest(){
        Command cmd = mock(Command.class);
        assertTrue(MenuItemsFactory.instance().createOpenMenuItem(cmd) instanceof MyMenuItem);
    }

    @Test
    public void createExitMenuItemTest(){
        Command cmd = mock(Command.class);
        assertTrue(MenuItemsFactory.instance().createExitMenuItem(cmd) instanceof MyMenuItem);
    }

    @Test
    public void createPlayMenuItemTest(){
        Command cmd = mock(Command.class);
        assertTrue(MenuItemsFactory.instance().createPlayMenuItem(cmd) instanceof MyMenuItem);
    }

    @Test
    public void createStopMenuItemTest(){
        Command cmd = mock(Command.class);
        assertTrue(MenuItemsFactory.instance().createStopMenuItem(cmd) instanceof MyMenuItem);
    }

    @Test
    public void createPauseMenuItemTest(){
        Command cmd = mock(Command.class);
        assertTrue(MenuItemsFactory.instance().createPauseMenuItem(cmd) instanceof MyMenuItem);
    }

    @Test
    public void createExportLogMenuItemTest(){
        Command cmd = mock(Command.class);
        assertTrue(MenuItemsFactory.instance().createExportLogMenuItem(cmd) instanceof MyMenuItem);
    }

    /*
    @Ignore
    @Test
    public void createExportLogMenuItemTest(){
        /* cmd = mock(Command.class);

        MyMenuItem menu = MenuItemsFactory.instance().createExportLogMenuItem(cmd);

        MyMenuItem expected = mock(MyMenuItem.class);
        when(expected.getId()).thenReturn(3);

        //when(expected.getId()).thenCallRealMethod();


        assertEquals(expected.getId(), menu.getId());

        //assertTrue(MenuItemsFactory.instance().createExportLogMenuItem(null) instanceof MyMenuItem);
    }*/

}