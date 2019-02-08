package ch.supsi.bthread.model;

public class ThreadS extends Element {
    private String threadId;
    private String status;

    public ThreadS(String threadId, String status) {
        this.threadId = threadId;
        this.status = status;
    }

    public String getThreadId() {
        return threadId;
    }

    public void setThreadId(String threadId) {
        this.threadId = threadId;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }
}
