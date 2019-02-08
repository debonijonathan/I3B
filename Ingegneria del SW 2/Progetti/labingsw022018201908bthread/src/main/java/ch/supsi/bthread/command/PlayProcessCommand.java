package ch.supsi.bthread.command;


import ch.supsi.bthread.Main;
import ch.supsi.bthread.controller.ProcessController;
import ch.supsi.bthread.iface.Command;

public class PlayProcessCommand implements Command {

    private ProcessController receiver;
    private String path = null;

    private PlayProcessCommand() {
    }

    public static PlayProcessCommand create(ProcessController receiver) {
        if (receiver == null) {
            return null;
        }

        PlayProcessCommand command = new PlayProcessCommand();
        command.receiver = receiver;
        return command;
    }

    public void setPath(String path){
        this.path = path;
    }

    public String getPath(){
        return path;
    }

    @Override
    public void execute() {
        if(path != null)
            receiver.playProcess(path);
    }

}
