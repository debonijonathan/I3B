package ch.supsi.bthread.event;

public class ProcessLoadedEvent extends AbstractEvent{

    private String getId;

    public ProcessLoadedEvent(String id) {
        super();
        this.getId = id;
    }

    public String getGetId() {
        return getId;
    }
}
