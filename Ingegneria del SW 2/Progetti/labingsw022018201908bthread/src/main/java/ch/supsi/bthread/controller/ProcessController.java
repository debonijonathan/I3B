package ch.supsi.bthread.controller;

import ch.supsi.bthread.iface.ProcessManager;

public class ProcessController implements ProcessManager {

    private ProcessManager model;

    private ProcessController() {}

    public static ProcessController create(ProcessManager model) {
        if (model == null) {
            return null;
        }

        ProcessController controller = new ProcessController();
        controller.model = model;

        return controller;
    }

    public void playProcess(String path) {
        model.playProcess(path);
    }

    public void stopProcess() {
        model.stopProcess();
    }

    public void pauseProcess() {
        model.pauseProcess();
    }

}
