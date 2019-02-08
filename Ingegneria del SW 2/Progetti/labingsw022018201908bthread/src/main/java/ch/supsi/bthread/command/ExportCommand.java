package ch.supsi.bthread.command;

import ch.supsi.bthread.controller.MonitoringController;
import ch.supsi.bthread.iface.Command;

public class ExportCommand implements Command {
    private MonitoringController receiver;

    private ExportCommand() {
    }

    public static ExportCommand create(MonitoringController receiver) {
        if (receiver == null) {
            return null;
        }

        ExportCommand command = new ExportCommand();
        command.receiver = receiver;

        return command;
    }

    @Override
    public void execute() { receiver.exportLog(); }
}
