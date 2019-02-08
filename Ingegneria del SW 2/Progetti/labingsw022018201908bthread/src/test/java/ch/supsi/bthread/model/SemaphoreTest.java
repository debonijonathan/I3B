package ch.supsi.bthread.model;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class SemaphoreTest {
    @Test
    public void initialization(){
        Semaphore s = new Semaphore("a", "b", "c");
        assertEquals("a", s.getName());
        assertEquals("b", s.getSemaphoreId());
        assertEquals("c", s.getSemaphoreValue());
        assertNotEquals(null, s.getQueue());
    }

    @Test
    public void addToQueue(){
        Semaphore s = new Semaphore("a", "b", "c");
        s.addToQueue("1st");
        assertEquals("1st", s.getQueue().get(0));
        assertEquals(1, s.getQueue().size());
    }

    @Test
    public void removeFromQueue(){
        Semaphore s = new Semaphore("a", "b", "c");
        s.addToQueue("1st");
        assertEquals("1st", s.getQueue().get(0));
        assertEquals(1, s.getQueue().size());
        s.removeFromQueue();
        assertEquals(0, s.getQueue().size());
    }

    @Test
    public void getQueueAsString(){
        Semaphore s= new Semaphore("a", "b", "c");
        s.addToQueue("1st");
        s.addToQueue("2nd");
        assertEquals("1st, 2nd", s.getQueueAsString());
    }
}