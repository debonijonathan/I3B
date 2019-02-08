package ch.supsi.bthread.model;

import ch.supsi.bthread.event.*;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Observable;
import java.util.concurrent.ConcurrentHashMap;

public class Scheduler extends Observable {
    private static Scheduler scheduler;

    private Map<String, Semaphore> semaphores;
    private Map<String, Mutex> mutexes;
    private Map<String, Barrier> barriers;
    private Map<String, ConditionVariable> conditionVariables;
    private Map<String, ThreadS> threadStatus;

    public static Scheduler instance() {
        if (scheduler == null) {
            scheduler = new Scheduler();
        }

        return scheduler;
    }

    private Scheduler() {
        //this.threads = new HashMap<>();
        mutexes = new ConcurrentHashMap<>();
        semaphores = new ConcurrentHashMap<>();
        barriers = new ConcurrentHashMap<>();
        conditionVariables = new ConcurrentHashMap<>();
        threadStatus = new ConcurrentHashMap<>();
    }

    public void clear(){
        semaphores.clear();
        mutexes.clear();
        barriers.clear();
        conditionVariables.clear();
        threadStatus.clear();
    }

    public void addThread(ThreadS thread, String threadId){
        if (!threadStatus.containsKey(thread.getThreadId()))
            threadStatus.put(thread.getThreadId(), thread);
        else{
            threadStatus.replace(threadId, thread);
        }

        setChanged();
        notifyObservers(new NewRowThreadStatus());
    }

    public void addSemaphore(Semaphore semaphore, String threadId){
        if (!semaphores.containsKey(semaphore.getSemaphoreId())) {
            semaphores.put(semaphore.getSemaphoreId(), semaphore);
        }
            //System.out.println("SCHEDULER: "+ semaphore.getName() + " "+ threadId + " "+ semaphore.getSemaphoreId() + " "+ semaphore.getSemaphoreValue() + " ");
            if(semaphore.getName().equals("(SEMWAIT)") && semaphore.getSemaphoreValue().equals("0")){
                semaphores.get(semaphore.getSemaphoreId()).addToQueue(threadId);
            }else if(semaphore.getName().equals(("(SEMPOST)")) && !semaphore.getQueue().isEmpty() && semaphore.getSemaphoreValue().equals("0")){
                semaphores.get(semaphore.getSemaphoreId()).removeFromQueue();
            }else if(semaphore.getName().equals("(SEMACQUIRE)")) {

            }else if(semaphore.getName().equals("(SEMBLOCKED)")){
                changeThreadStatus(threadId, "BLOCKED");
            }else{
                semaphores.replace(semaphore.getSemaphoreId(), semaphore);
            }


        setChanged();
        notifyObservers(new NewRowSemaphore());
    }

    public Map<String, Semaphore> getSemaphores() {
        return semaphores;
    }

    public void addConditionVariables(ConditionVariable conditionVariable, String threadId){
        if (!conditionVariables.containsKey(conditionVariable.getVariableId()))
            conditionVariables.put(conditionVariable.getVariableId(), conditionVariable);

        if(conditionVariable.getName().equals("(CONDBLOCKED)")){
            scheduler.getConditionVariables().get(conditionVariable.getVariableId()).addToQueue(threadId);
            changeThreadStatus(threadId, "BLOCKED");
            //System.out.println(threadId + " block");
        }else if(conditionVariable.getName().equals("(CONDSIGNAL)")&&!scheduler.getConditionVariables().get(conditionVariable.getVariableId()).getQueue().isEmpty()){
            changeThreadStatus(scheduler.getConditionVariables().get(conditionVariable.getVariableId()).getQueue().get(0), "READY");
            //System.out.println(scheduler.getConditionVariables().get(conditionVariable.getVariableId()).getQueue().get(0) + " READY");
            scheduler.getConditionVariables().get(conditionVariable.getVariableId()).removeFromQueue();
        }else if(conditionVariable.getName().equals("(CONDBROADCAST)")&&!scheduler.getConditionVariables().get(conditionVariable.getVariableId()).getQueue().isEmpty()){
            for(String s : scheduler.getConditionVariables().get(conditionVariable.getVariableId()).getQueue()){
                changeThreadStatus(s, "READY");
            }
            scheduler.getConditionVariables().get(conditionVariable.getVariableId()).getQueue().clear();
        }
//        conditionVariables.replace(conditionVariable.getVariableId(), conditionVariable);

        setChanged();
        notifyObservers(new NewRowCondVar());
    }

    public Map<String, ConditionVariable> getConditionVariables() {
        return conditionVariables;
    }

    public void addMutex(Mutex mutex, String threadId){
//        System.out.println("add mut");
        if (!mutexes.containsKey(mutex.getMutexId())){
            mutexes.put(mutex.getMutexId(), mutex);
        }

        if(mutex.getName().equals("(MUTRELEASE)")){
            mutexes.get(mutex.getMutexId()).setOwner("");
            changeThreadStatus(threadId, "READY");
        }else if(mutex.getName().equals("(MUTBLOCKED)")){
            scheduler.changeThreadStatus(threadId, "BLOCKED");
            mutexes.get(mutex.getMutexId()).addToQueue(threadId);
        }else if(mutex.getName().equals("(MUTACQUIRE)")){
            changeThreadStatus(threadId, "READY");
            mutexes.get(mutex.getMutexId()).setOwner(threadId);
            if(!mutexes.get(mutex.getMutexId()).getQueue().isEmpty()){
                if (mutexes.get(mutex.getMutexId()).getQueue().get(0).equals(threadId)){
                    mutex.removeFromQueue();
                }
            }
        }
        mutexes.replace(mutex.getMutexId(), mutex);

        setChanged();
        notifyObservers(new NewRowMutex());
    }

    public Map<String, Mutex> getMutexes() {
        return mutexes;
    }

    public void addBarrier(Barrier barrier, String threadId){
        if (!barriers.containsKey(barrier.getBarrierId()))
            barriers.put(barrier.getBarrierId(), barrier);
        if(barrier.getName().equals("(BARRIERWAIT)")){
            barriers.get(barrier.getBarrierId()).addToQueue(threadId);
        }else if(barrier.getName().equals("(BARRIERBLOCKED)")){
            changeThreadStatus(threadId, "BLOCKED");
        }else if(barrier.getName().equals("(BARRIERUNLOCK)")){

        }
        barriers.replace(barrier.getBarrierId(), barrier);
        setChanged();
        notifyObservers(new NewRowBarrier());
    }

    public void changeThreadStatus(String threadId, String status){
        //System.out.println("Change "+ threadId+ " from "+ threadStatus.get(threadId).getStatus() + " to "+ status);
        setChanged();
        threadStatus.get(threadId).setStatus(status);
        //System.out.println("Status after change "+ threadStatus.get(threadId).getStatus());
        notifyObservers(new NewRowThreadStatus());
    }

    public Map<String, Barrier> getBarriers() {
        return barriers;
    }

    public Map<String, ThreadS> getThreadStatus() {
        return threadStatus;
    }
}