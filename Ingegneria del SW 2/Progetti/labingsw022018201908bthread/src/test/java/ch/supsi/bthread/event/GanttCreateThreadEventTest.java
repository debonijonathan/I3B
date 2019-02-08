package ch.supsi.bthread.event;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class GanttCreateThreadEventTest {
    @Test
    public void getGetId() {
        GanttCreateThreadEvent gcte = new GanttCreateThreadEvent("1");
        assertEquals("1", gcte.getThreadId());
    }
}
