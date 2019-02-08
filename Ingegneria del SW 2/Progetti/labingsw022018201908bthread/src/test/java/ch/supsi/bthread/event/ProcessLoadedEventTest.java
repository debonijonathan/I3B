package ch.supsi.bthread.event;

import org.junit.Test;

import static org.junit.Assert.*;

public class ProcessLoadedEventTest {

    @Test
    public void getGetId() {
        ProcessLoadedEvent ple = new ProcessLoadedEvent("1");
        assertEquals("1", ple.getGetId());
    }
}