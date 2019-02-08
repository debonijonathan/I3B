package ch.supsi.bthread.event;

public class ProcessNotStartedEvent {

    private String filename;

    public ProcessNotStartedEvent(String filename) {
        super();
        this.filename = filename;
    }

    public String getFilename() {
        return filename;
    }

}
