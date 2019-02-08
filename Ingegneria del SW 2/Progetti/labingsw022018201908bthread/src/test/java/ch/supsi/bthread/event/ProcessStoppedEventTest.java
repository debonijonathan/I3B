package ch.supsi.bthread.event;

import org.junit.Test;

import static org.junit.Assert.*;

public class ProcessStoppedEventTest {

    @Test
    public void getId() {
        ProcessStoppedEvent pse = new ProcessStoppedEvent("1");
        assertEquals("1",pse.getId());
    }
}