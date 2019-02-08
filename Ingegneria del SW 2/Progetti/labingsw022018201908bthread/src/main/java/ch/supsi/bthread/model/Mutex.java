package ch.supsi.bthread.model;

import java.util.ArrayList;

public class Mutex extends Element{
    private String owner;
    private String mutexId;
    private ArrayList<String> queue;

    public Mutex(String name, String mutexId) {
        this.setName(name);
        this.mutexId = mutexId;
        queue = new ArrayList<>();
    }

    public String getOwner() {
        return owner;
    }

    public void setOwner(String owner) {
        this.owner = owner;
    }

    public String getMutexId() {
        return mutexId;
    }

    public void setMutexId(String mutexId) {
        this.mutexId = mutexId;
    }

    public void addToQueue(String thread){
        queue.add(thread);
    }

    public void removeFromQueue(){
        queue.remove(0);
    }

    public ArrayList<String> getQueue(){
        return queue;
    }

    public String getQueueAsString(){
        String output = "";
        for (String thr : queue)
            output += thr+", ";
        return output.substring(0, output.length()-2);
    }

    public boolean hasOwner(){
        if (owner.equals(""))
            return false;
        return true;
    }
}
