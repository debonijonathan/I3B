package ch.supsi.bthread.view;

import ch.supsi.bthread.iface.Command;
import org.junit.Test;

import static junit.framework.TestCase.assertNull;
import static junit.framework.TestCase.assertTrue;
import static org.mockito.Mockito.mock;

public class MyRadioItemTest {
    @Test
    public void getActualComponent(){
        assertNull(new MyRadioItem().getActualComponent());
    }

    @Test
    public void create(){
        Command cmd = mock(Command.class);
        assertTrue(MyRadioItem.create(new String(),cmd) instanceof  MyRadioItem);
    }
}