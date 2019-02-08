package ch.supsi.bthread.model;

import org.junit.Test;

import static org.junit.Assert.*;

public class ConditionVariableTest {

    @Test
    public void inatialization(){
        ConditionVariable cv = new ConditionVariable("a", "b");
        assertEquals("a", cv.getName());
        assertEquals("b", cv.getVariableId());
        assertNotEquals(null, cv.getQueue());
    }

    @Test
    public void addToQueue(){
        ConditionVariable cv = new ConditionVariable("a", "b");
        cv.addToQueue("1st");
        assertEquals("1st", cv.getQueue().get(0));
        assertEquals(1, cv.getQueue().size());
    }

    @Test
    public void removeFromQueue(){
        ConditionVariable cv = new ConditionVariable("a", "b");
        cv.addToQueue("1st");
        cv.removeFromQueue();
        assertEquals(0, cv.getQueue().size());
    }

    @Test
    public void getQueueAsString(){
        ConditionVariable cv = new ConditionVariable("a", "b");
        cv.addToQueue("1st");
        cv.addToQueue("2nd");
        assertEquals("1st, 2nd", cv.getQueueAsString());
    }
}