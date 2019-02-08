package ch.supsi.bthread.view;

import ch.supsi.bthread.iface.Command;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;


public class MenuItemsFactory {

    private static MenuItemsFactory factory;

    protected MenuItemsFactory() {}

    public static MenuItemsFactory instance() {
        if (factory == null) {
            factory = new MenuItemsFactory();
        }
        return factory;
    }

    private ImageView setImage(String path){
        Image image = new Image("/"+path);
        ImageView imageView = new ImageView(image);
        imageView.setFitWidth(15);
        imageView.setFitHeight(15);
        return imageView;
    }

    public MyMenuItem createExportLogMenuItem(Command command) {
        MyMenuItem myMenuItem = MyMenuItem.create("Export Log", command);
        myMenuItem.setId("exportLogMenuItem");
        myMenuItem.menuItem.setGraphic(setImage("export.png"));
        return myMenuItem;
    }

    public MyMenuItem createTracingMenuItem(Command command) {
        MyMenuItem myMenuItem = MyMenuItem.create("Tracing", command);
        myMenuItem.setId("tracingMenuItem");
        myMenuItem.menuItem.setGraphic(setImage("tracing.png"));
        return myMenuItem;
    }

    public MyRadioItem createShowMenuItem(Command command) {
        MyRadioItem myMenuItem = MyRadioItem.create("Hide Console", command);
        myMenuItem.setId("commandLineMenuItem");
        //myMenuItem.menuItem.setGraphic(setImage("view.png"));
        return myMenuItem;
    }

    public MyMenuItem createOpenMenuItem(Command command) {
        MyMenuItem myMenuItem = MyMenuItem.create("Open", command);
        myMenuItem.setId("openMenuItem");
        myMenuItem.menuItem.setGraphic(setImage("open.png"));
        return myMenuItem;
    }

    public MyMenuItem createExitMenuItem(Command command) {
        MyMenuItem myMenuItem = MyMenuItem.create("Exit", command);
        myMenuItem.setId("exitMenuItem");
        myMenuItem.menuItem.setGraphic(setImage("exit.png"));
        return myMenuItem;
    }

    public MyMenuItem createPlayMenuItem(Command command) {
        MyMenuItem myMenuItem = MyMenuItem.create("Play", command);
        myMenuItem.setId("startProcessMenuItem");
        myMenuItem.menuItem.setGraphic(setImage("play.png"));
        return myMenuItem;
    }

    public MyMenuItem createStopMenuItem(Command command) {
        MyMenuItem myMenuItem = MyMenuItem.create("Stop", command);
        myMenuItem.setId("stopProcessMenuItem");
        myMenuItem.menuItem.setGraphic(setImage("stop.png"));
        return myMenuItem;
    }

    public MyMenuItem createPauseMenuItem(Command command) {
        MyMenuItem myMenuItem = MyMenuItem.create("Pause", command);
        myMenuItem.setId("pauseProcessMenuItem");
        myMenuItem.menuItem.setGraphic(setImage("pause.png"));
        return myMenuItem;
    }

}
