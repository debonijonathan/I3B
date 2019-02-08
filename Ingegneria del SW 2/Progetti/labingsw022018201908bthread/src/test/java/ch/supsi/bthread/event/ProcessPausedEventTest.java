package ch.supsi.bthread.event;

import org.junit.Test;

import static org.junit.Assert.*;

public class ProcessPausedEventTest {

    @Test
    public void getId() {
        ProcessPausedEvent ppe = new ProcessPausedEvent("1");
        assertEquals("1", ppe.getId());
    }
}