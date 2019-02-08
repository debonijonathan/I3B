package ch.supsi.bthread.event;


public class NewLineReadEvent extends AbstractEvent{

    private String line;

    public NewLineReadEvent(String line) {
        this.line = line;
    }

    public String getLine() {
        return line;
    }

}
