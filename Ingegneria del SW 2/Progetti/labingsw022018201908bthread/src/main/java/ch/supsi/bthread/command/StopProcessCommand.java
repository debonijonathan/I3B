package ch.supsi.bthread.command;

import ch.supsi.bthread.iface.Command;
import ch.supsi.bthread.iface.ProcessManager;

public class StopProcessCommand implements Command {

    private ProcessManager receiver;

    private StopProcessCommand() {
    }

    public static StopProcessCommand create(ProcessManager receiver) {
        if (receiver == null) {
            return null;
        }

        StopProcessCommand command = new StopProcessCommand();
        command.receiver = receiver;

        return command;
    }

    @Override
    public void execute() {
        receiver.stopProcess();
    }

}
