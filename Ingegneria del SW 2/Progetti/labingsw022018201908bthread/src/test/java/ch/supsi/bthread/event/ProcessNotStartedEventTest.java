package ch.supsi.bthread.event;

import org.junit.Test;

import static org.junit.Assert.*;

public class ProcessNotStartedEventTest {

    @Test
    public void getFilename() {
        ProcessNotStartedEvent pnse = new ProcessNotStartedEvent("filename");
        assertEquals("filename", pnse.getFilename());
    }
}