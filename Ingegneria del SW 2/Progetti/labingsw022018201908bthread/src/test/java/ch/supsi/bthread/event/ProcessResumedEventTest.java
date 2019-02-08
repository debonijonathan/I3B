package ch.supsi.bthread.event;

import org.junit.Test;

import static org.junit.Assert.*;

public class ProcessResumedEventTest {

    @Test
    public void getGetId() {
        ProcessResumedEvent pre = new ProcessResumedEvent("1");
        assertEquals("1", pre.getGetId());
    }
}