package ch.supsi.bthread.event;

public class ProcessResumedEvent extends AbstractEvent{

    private String getId;

    public ProcessResumedEvent(String id) {
        super();
        this.getId = id;
    }

    public String getGetId() {
        return getId;
    }

}
