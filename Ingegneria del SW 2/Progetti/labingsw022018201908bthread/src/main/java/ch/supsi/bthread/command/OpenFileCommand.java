package ch.supsi.bthread.command;

import ch.supsi.bthread.controller.ProcessController;
import ch.supsi.bthread.iface.Command;
import ch.supsi.bthread.mediator.MenuBarMediator;

public class OpenFileCommand implements Command {

    private MenuBarMediator receiver;

    private OpenFileCommand() {
    }

    public static OpenFileCommand create(MenuBarMediator receiver) {
        if (receiver == null) {
            return null;
        }

        OpenFileCommand command = new OpenFileCommand();
        command.receiver = receiver;
        return command;
    }

    @Override
    public void execute() {
        receiver.openPath();
    }
}