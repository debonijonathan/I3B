package ch.supsi.bthread.controller;


import ch.supsi.bthread.iface.MonitoringManager;

public class MonitoringController implements MonitoringManager {

    private MonitoringManager model;

    private MonitoringController() {}

    public static MonitoringController create(MonitoringManager model) {
        if (model == null) {
            return null;
        }

        MonitoringController controller = new MonitoringController();
        controller.model = model;

        return controller;
    }

    @Override
    public void exportLog() { model.exportLog(); }

}
