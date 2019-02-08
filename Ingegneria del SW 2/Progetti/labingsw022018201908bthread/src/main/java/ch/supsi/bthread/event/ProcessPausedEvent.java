package ch.supsi.bthread.event;

public class ProcessPausedEvent extends AbstractEvent {

    private String id;

    public ProcessPausedEvent(String id) {
        super();
        this.id = id;
    }

    public String getId() {
        return id;
    }

}