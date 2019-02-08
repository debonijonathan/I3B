package ch.supsi.bthread.model;
import java.util.ArrayList;

public class Semaphore extends Element{

    private String semaphoreId;
    private String semaphoreValue;
    private ArrayList<String> queue;

    public Semaphore(String name, String semaphoreId, String semaphoreValue) {
        this.setName(name);
        this.semaphoreId = semaphoreId;
        this.semaphoreValue = semaphoreValue;
        queue = new ArrayList<>();
    }

    public Semaphore(String name) {
        this(name, "", "");
    }

    public String getSemaphoreId() {
        return semaphoreId;
    }

    public void setSemaphoreId(String semaphoreId) {
        this.semaphoreId = semaphoreId;
    }

    public String getSemaphoreValue() {
        return semaphoreValue;
    }

    public void setSemaphoreValue(String semaphoreValue) {
        this.semaphoreValue = semaphoreValue;
    }

    public void addToQueue(String threadId){
        queue.add(threadId);
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
}
