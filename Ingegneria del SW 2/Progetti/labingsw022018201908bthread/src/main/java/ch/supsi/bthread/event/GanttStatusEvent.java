package ch.supsi.bthread.event;

public class GanttStatusEvent extends AbstractEvent{

    private String getId;

    public GanttStatusEvent(String id) {
        super();
        this.getId = id;
    }

    public String getGetId() {
        return getId;
    }
}
