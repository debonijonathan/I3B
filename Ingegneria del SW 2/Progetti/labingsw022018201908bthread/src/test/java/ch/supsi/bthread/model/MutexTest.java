package ch.supsi.bthread.model;

import org.junit.Test;

import static org.junit.Assert.*;

public class MutexTest {

    @Test
    public void inatialization(){
        Mutex m = new Mutex("a", "b");
        assertEquals("a", m.getName());
        assertEquals("b", m.getMutexId());
    }

    @Test
    public void addToQueue(){
        Mutex m = new Mutex("a", "b");

    }
}