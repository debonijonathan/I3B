package ch.supsi.bthread.controller;


import ch.supsi.bthread.iface.ExitManager;

public class ExitController implements ExitManager {

    private ExitManager model;

    private ExitController() {}

    public static ExitController create(ExitManager model) {
        if (model == null) {
            return null;
        }

        ExitController controller = new ExitController();
        controller.model = model;

        return controller;
    }

    @Override
    public void exit() {
        if (model != null)
            model.exit();
    }

}
