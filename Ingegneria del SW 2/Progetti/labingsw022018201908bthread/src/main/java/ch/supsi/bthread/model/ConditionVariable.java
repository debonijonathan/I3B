package ch.supsi.bthread.model;

import java.util.ArrayList;

public class ConditionVariable extends Element{
    private String variableId;
    private ArrayList<String> queue;

    public ConditionVariable(String name, String variableId) {
        this.setName(name);
        queue = new ArrayList<>();

        this.variableId = variableId;
    }

    public String getVariableId() {
        return variableId;
    }

    public void setVariableId(String variableId) {
        this.variableId = variableId;
    }

    public void addToQueue(String threadId){
        queue.add(threadId);
    }

    public void removeFromQueue(){
        if (!queue.isEmpty())
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
