package ch.supsi.bthread.view;

import ch.supsi.bthread.iface.Command;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.RadioMenuItem;

public class MyRadioItem {

    protected RadioMenuItem menuItem;

    protected MyRadioItem() {
    }

    public static MyRadioItem create(String text, Command command) {
        MyRadioItem myMenuItem = new MyRadioItem();

        myMenuItem.menuItem = new RadioMenuItem(text);
        myMenuItem.menuItem.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent e) {
                if (command != null) {
                    command.execute();
                }
            }
        });

        return myMenuItem;
    }

    public RadioMenuItem getActualComponent() {
        return menuItem;
    }

    public void setId(String id) {
        if (id == null || id.isEmpty()) {
            return;
        }

        menuItem.setId(id);
    }

    public void enable() {
        menuItem.setDisable(false);
    }

    public void disable() {
        menuItem.setDisable(true);
    }
}
