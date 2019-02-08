package ch.supsi.bthread.command;

import ch.supsi.bthread.iface.Command;
import ch.supsi.bthread.iface.ProcessManager;

public class PauseProcessCommand implements Command {
    private ProcessManager receiver;

    private PauseProcessCommand() {
    }

    public static PauseProcessCommand create(ProcessManager receiver) {
        if (receiver == null) {
            return null;
        }

        PauseProcessCommand command = new PauseProcessCommand();
        command.receiver = receiver;

        return command;
    }

    @Override
    public void execute() {
        receiver.pauseProcess();
    }
}
