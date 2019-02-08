package ch.supsi.bthread.event;

import org.junit.Test;

import static org.junit.Assert.*;

public class ProcessStartedEventTest {

    @Test
    public void getGetId() {
        ProcessStartedEvent pse = new ProcessStartedEvent("1");
        assertEquals("1", pse.getGetId());
    }
}