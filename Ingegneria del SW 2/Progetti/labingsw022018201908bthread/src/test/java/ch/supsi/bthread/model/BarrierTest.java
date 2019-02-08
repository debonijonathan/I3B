package ch.supsi.bthread.model;

import org.junit.Test;

import static org.junit.Assert.*;

public class BarrierTest {

    @Test
    public void initialization(){
        Barrier b = new Barrier("a", "b", "c", "d");
        assertEquals("a" , b.getName());
        assertEquals("b" , b.getWaitQueueSize());
        assertEquals("c" , b.getBarrierId());
        assertEquals("d" , b.getBarrierSize());
        assertNotEquals(null , b.getQueue());
    }

    @Test
    public void addToQueue(){
        Barrier b = new Barrier("a", "b", "c", "d");
        b.addToQueue("1st");
        assertEquals("1st", b.getQueue().get(0));
        assertEquals(1, b.getQueue().size());
        assertEquals("1", b.getWaitQueueSize());
    }

    @Test
    public void removeFromQueue(){
        Barrier b = new Barrier("a", "b", "c", "d");
        b.addToQueue("1st");
        b.removeFromQueue();
        assertEquals(0, b.getQueue().size());
        assertEquals("0", b.getWaitQueueSize());
    }

    @Test
    public void getQueueAsString(){
        Barrier b = new Barrier("a", "b", "c", "d");
        b.addToQueue("1st");
        b.addToQueue("2nd");
        assertEquals("1st, 2nd", b.getQueueAsString());
    }
}