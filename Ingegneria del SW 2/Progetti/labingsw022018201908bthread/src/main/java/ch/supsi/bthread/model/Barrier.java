package ch.supsi.bthread.model;

import java.util.ArrayList;

public class Barrier extends Element{
    private String waitQueueSize;
    private String barrierId;
    private String barrierSize;
    private ArrayList<String> queue;

    public Barrier(String name, String waitQueueSize, String barrierId, String barrierSize) {
        this.setName(name);
        this.waitQueueSize = waitQueueSize;
        this.barrierId = barrierId;
        this.barrierSize = barrierSize;
        queue = new ArrayList<>();
    }

    public String getWaitQueueSize() {
        return waitQueueSize;
    }

    public void setWaitQueueSize(String waitQueueSize) {
        this.waitQueueSize = waitQueueSize;
    }

    public String getBarrierId() {
        return barrierId;
    }

    public void setBarrierId(String barrierId) {
        this.barrierId = barrierId;
    }

    public String getBarrierSize() {
        return barrierSize;
    }

    public void setBarrierSize(String barrierSize) {
        this.barrierSize = barrierSize;
    }

    public void addToQueue(String threadId){
        queue.add(threadId);
        waitQueueSize = queue.size()+"";
    }

    public void removeFromQueue(){
        if(!queue.isEmpty()){
            queue.remove(0);
            waitQueueSize = queue.size()+"";
        }
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
}
