package ch.supsi.bthread.model;

public abstract class Element {
    private String name;

    public String getName(){
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}
