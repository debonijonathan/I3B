package ch.supsi.bthread.command;


import ch.supsi.bthread.controller.ExitController;
import ch.supsi.bthread.iface.Command;

public class ExitCommand implements Command {

    private ExitController receiver;

    private ExitCommand() {}

    public static ExitCommand create(ExitController receiver) {
        if (receiver == null) {
            return null;
        }

        ExitCommand command = new ExitCommand();
        command.receiver = receiver;

        return command;
    }

    @Override
    public void execute() {
        receiver.exit();
    }

}
