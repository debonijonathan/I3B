package ch.supsi.bthread.event;

import org.junit.Test;

import static org.junit.Assert.*;

public class NewLockStatusEventTest {
    NewLockStatusEvent nlse = new NewLockStatusEvent("tipo", "valore", "id","memoria");
    @Test
    public void getType() {
        assertEquals("tipo",nlse.getType());
    }

    @Test
    public void getValue() {
        assertEquals("valore",nlse.getValue());
    }

    @Test
    public void getId() {
        assertEquals("id",nlse.getId());
    }

    @Test
    public void getMemory() {
        assertEquals("memoria",nlse.getMemory());
    }
}