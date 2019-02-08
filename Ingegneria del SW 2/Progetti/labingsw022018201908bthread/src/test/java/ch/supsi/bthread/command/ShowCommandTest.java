package ch.supsi.bthread.command;

import ch.supsi.bthread.view.ConsoleView;
import org.junit.Test;

import static junit.framework.TestCase.assertTrue;
import static org.mockito.Mockito.mock;

public class ShowCommandTest {
    @Test
    public void create() {
        ConsoleView pm = mock(ConsoleView.class);
        assertTrue(ShowCommand.create(pm) instanceof ShowCommand);
    }
}
