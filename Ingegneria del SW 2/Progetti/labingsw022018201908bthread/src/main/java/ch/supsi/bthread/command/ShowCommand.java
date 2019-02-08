package ch.supsi.bthread.command;

import ch.supsi.bthread.iface.Command;
import ch.supsi.bthread.mediator.MenuBarMediator;
import ch.supsi.bthread.view.ConsoleView;

public class ShowCommand implements Command {

    private ConsoleView receiver;

    private ShowCommand() {
    }

    public static ShowCommand create(ConsoleView receiver) {
        if (receiver == null) {
            return null;
        }

        ShowCommand command = new ShowCommand();
        command.receiver = receiver;
        return command;
    }

    @Override
    public void execute() {
        receiver.changeStatusCommandLine();
    }
}