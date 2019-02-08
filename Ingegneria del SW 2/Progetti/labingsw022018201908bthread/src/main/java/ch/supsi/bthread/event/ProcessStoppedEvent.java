package ch.supsi.bthread.event;


public class ProcessStoppedEvent extends AbstractEvent {

    private String id;

    public ProcessStoppedEvent(String id) {
        super();
        this.id = id;
    }

    public String getId() {
        return id;
    }

}
