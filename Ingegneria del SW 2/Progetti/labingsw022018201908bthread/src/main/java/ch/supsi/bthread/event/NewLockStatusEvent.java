package ch.supsi.bthread.event;

public class NewLockStatusEvent extends  AbstractEvent {

    private String type;
    private String value;
    private String id;
    private String memory;

    public NewLockStatusEvent(String type, String value, String id, String memory) {
        this.type = type;
        this.value = value;
        this.id = id;
        this.memory = memory;
    }

    public String getType() {
        return type;
    }

    public String getValue() {
        return value;
    }

    public String getId() {
        return id;
    }

    public String getMemory() {
        return memory;
    }
}
