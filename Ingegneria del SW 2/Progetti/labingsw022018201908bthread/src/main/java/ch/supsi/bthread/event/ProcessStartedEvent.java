package ch.supsi.bthread.event;


public class ProcessStartedEvent extends AbstractEvent {

    private String getId;

    public ProcessStartedEvent(String id) {
        super();
        this.getId = id;
    }

    public String getGetId() {
        return getId;
    }

}
