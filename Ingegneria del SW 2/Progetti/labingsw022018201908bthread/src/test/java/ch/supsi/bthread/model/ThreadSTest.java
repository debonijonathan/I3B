package ch.supsi.bthread.model;

import org.junit.Test;

import static org.junit.jupiter.api.Assertions.*;

public class ThreadSTest {

    @Test
    public void initialization(){
        ThreadS t = new ThreadS("a", "b");
        assertEquals("a", t.getThreadId());
        assertEquals("b", t.getStatus());

    }
}