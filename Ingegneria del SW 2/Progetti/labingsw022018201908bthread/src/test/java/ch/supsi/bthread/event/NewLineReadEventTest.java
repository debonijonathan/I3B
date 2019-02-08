package ch.supsi.bthread.event;

import org.junit.Test;

import static org.junit.Assert.*;

public class NewLineReadEventTest {

    @Test
    public void getLine() {
        NewLineReadEvent nre = new NewLineReadEvent("test");
        assertEquals("test", nre.getLine());
    }
}