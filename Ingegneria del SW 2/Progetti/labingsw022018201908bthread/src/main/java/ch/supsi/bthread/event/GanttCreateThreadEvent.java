package ch.supsi.bthread.event;

public class GanttCreateThreadEvent {
    private String threadId;

    public GanttCreateThreadEvent(String threadId){
        this.threadId = threadId;
    }

    public String getThreadId() {
        return threadId;
    }
}
