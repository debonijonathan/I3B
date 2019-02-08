package ch.supsi.bthread.event;

import org.junit.Test;

import static org.junit.Assert.*;

public class GanttStatusEventTest {

    @Test
    public void getGetId() {
        GanttStatusEvent gse = new GanttStatusEvent("1");
        assertEquals("1", gse.getGetId());
    }
}