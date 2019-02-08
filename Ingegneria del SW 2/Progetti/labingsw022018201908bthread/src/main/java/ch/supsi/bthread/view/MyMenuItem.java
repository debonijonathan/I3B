package ch.supsi.bthread.view;

import ch.supsi.bthread.iface.Command;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.MenuItem;


public class MyMenuItem {

    protected MenuItem menuItem;

    protected MyMenuItem() {
    }

    public static MyMenuItem create(String text, Command command) {
        MyMenuItem myMenuItem = new MyMenuItem();

        myMenuItem.menuItem = new MenuItem(text);
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

    public MenuItem getActualComponent() {
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
