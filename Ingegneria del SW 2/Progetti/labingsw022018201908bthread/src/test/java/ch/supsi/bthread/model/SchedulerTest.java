package ch.supsi.bthread.model;

import org.junit.jupiter.api.Test;
import org.mockito.Mock;
import org.mockito.Mockito;

import java.util.HashMap;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Matchers.shortThat;
import static org.mockito.Mockito.spy;
import static org.mockito.Mockito.times;

public class SchedulerTest {

    @Test
    public void inatialization(){
        Scheduler scheduler;
        scheduler = Scheduler.instance();

        assertNotEquals(null, scheduler.getThreadStatus());
        assertNotEquals(null, scheduler.getSemaphores());
        assertNotEquals(null, scheduler.getMutexes());
        assertNotEquals(null, scheduler.getBarriers());
        assertNotEquals(null, scheduler.getConditionVariables());
    }

    @Test
    public void addThread(){
        Scheduler scheduler;
        scheduler = Scheduler.instance();

        Map<Integer, String> a = new HashMap<>();
        a.put(0, "0");
        assertNotEquals(null, a.get(0));

        scheduler.addThread(new ThreadS("a", "b"), "a");
        assertNotEquals(null, scheduler.getThreadStatus().get("a"));
        assertEquals("a", scheduler.getThreadStatus().get("a").getThreadId());
        assertEquals("b", scheduler.getThreadStatus().get("a").getStatus());
    }

    @Test
    public void changeThreadStatus(){
        Scheduler scheduler;
        scheduler = Scheduler.instance();

        scheduler.addThread(new ThreadS("a", "b"), "a");
        assertNotEquals(null, scheduler.getThreadStatus().get("a"));
        assertEquals("a", scheduler.getThreadStatus().get("a").getThreadId());
        assertEquals("b", scheduler.getThreadStatus().get("a").getStatus());

        scheduler.changeThreadStatus("a", "c");
        assertEquals("c", scheduler.getThreadStatus().get("a").getStatus());
    }


    @Test
    public void addSemaphore(){
        Scheduler scheduler;
        scheduler = Mockito.spy(Scheduler.instance());
        Semaphore spySemaphore = Mockito.spy(new Semaphore("name", "sid", "value"));

        scheduler.addSemaphore(spySemaphore, "tid");
        Mockito.verify(spySemaphore, times(3)).getSemaphoreId();
        assertEquals(spySemaphore, scheduler.getSemaphores().get("sid"));

        spySemaphore.setName("(SEMWAIT)");
        spySemaphore.setSemaphoreValue("0");
        scheduler.addSemaphore(spySemaphore, "tid");
        assertNotEquals(0, scheduler.getSemaphores().get("sid").getQueue().size());
        Mockito.verify(spySemaphore, times(1)).addToQueue("tid");

        spySemaphore.setName("(SEMPOST)");
        scheduler.addSemaphore(spySemaphore, "tid");
        Mockito.verify(spySemaphore, times(1)).removeFromQueue();
        assertEquals(0, scheduler.getSemaphores().get("sid").getQueue().size());
    }

    @Test
    public void addMutex(){
        Scheduler scheduler;
        scheduler = Mockito.spy(Scheduler.instance());
        Mutex mutex = Mockito.spy(new Mutex("name", "mid"));
        ThreadS thread = new ThreadS("tid", "status");

        scheduler.addThread(thread, "tid");
        scheduler.addMutex(mutex, "tid");
        Mockito.verify(mutex, times(3)).getMutexId();
        assertEquals(mutex, scheduler.getMutexes().get("mid"));

        mutex.setName("(MUTRELEASE)");
        scheduler.addMutex(mutex, "tid");
        Mockito.verify(mutex, times(1)).setOwner("");
        Mockito.verify(scheduler, times(1)).changeThreadStatus("tid", "READY");
        assertEquals("READY", scheduler.getThreadStatus().get("tid").getStatus());

        mutex.setName("(MUTBLOCKED)");
        scheduler.addMutex(mutex, "tid");
        Mockito.verify(mutex, times(1)).addToQueue("tid");
        assertNotEquals(0, scheduler.getMutexes().get("mid").getQueue().size());
        Mockito.verify(scheduler, times(1)).changeThreadStatus("tid", "BLOCKED");

        mutex.setName("(MUTACQUIRE)");
        scheduler.addMutex(mutex, "tid");
        Mockito.verify(mutex, times(1)).setOwner("tid");
        //Mockito.verify(scheduler, times(1)).changeThreadStatus("tid", "READY");
        assertEquals("READY", scheduler.getThreadStatus().get("tid").getStatus());
    }

    @Test
    public void addBarrier(){
        Scheduler scheduler;
        scheduler = Mockito.spy(Scheduler.instance());
        Barrier barrier = Mockito.spy(new Barrier("name", "qs", "bid", "bs"));
        ThreadS thread = new ThreadS("tid", "status");

        scheduler.addThread(thread, "tid");
        scheduler.addBarrier(barrier, "tid");
        Mockito.verify(barrier, times(3)).getBarrierId();
        assertEquals(barrier, scheduler.getBarriers().get("bid"));

        barrier.setName("(BARRIERWAIT)");
        scheduler.addBarrier(barrier, "tid");
        Mockito.verify(barrier, times(1)).addToQueue("tid");

        barrier.setName("(BARRIERBLOCKED)");
        scheduler.addBarrier(barrier, "tid");
        Mockito.verify(scheduler, times(1)).changeThreadStatus("tid", "BLOCKED");
    }

    @Test
    public void addConditionalVariables(){
        Scheduler scheduler;
        scheduler = Mockito.spy(Scheduler.instance());
        ConditionVariable conditionVariable = Mockito.spy(new ConditionVariable("name", "cvid"));
        ThreadS thread = new ThreadS("tid", "status");

        scheduler.addThread(thread, "tid");
        scheduler.addConditionVariables(conditionVariable, "tid");
        Mockito.verify(conditionVariable, times(2)).getVariableId();
        assertEquals(conditionVariable, scheduler.getConditionVariables().get("cvid"));

        conditionVariable.addToQueue("tid");

        conditionVariable.setName("(CONDSIGNAL)");
        scheduler.addConditionVariables(conditionVariable, "tid");
        Mockito.verify(conditionVariable, times(1)).removeFromQueue();
        Mockito.verify(scheduler, times(1)).changeThreadStatus("tid", "READY");

        conditionVariable.addToQueue("tid");

        conditionVariable.setName("(CONDBROADCAST)");
        scheduler.addConditionVariables(conditionVariable, "tid");
        //Mockito.verify(scheduler, times(1)).changeThreadStatus("tid", "READY");
        Mockito.verify(conditionVariable, times(5)).getQueue();
        assertEquals(0, scheduler.getConditionVariables().get("cvid").getQueue().size());
    }
}