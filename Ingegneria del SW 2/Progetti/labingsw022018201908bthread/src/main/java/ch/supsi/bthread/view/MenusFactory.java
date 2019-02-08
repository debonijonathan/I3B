package ch.supsi.bthread.view;


import javafx.scene.control.Menu;

public class MenusFactory {

    private static MenusFactory factory;

    protected MenusFactory() {}

    public static MenusFactory instance() {
        if (factory == null) {
            factory = new MenusFactory();
        }
        return factory;
    }

    public Menu createFileMenu() {
        Menu menu = new Menu();
        menu.setText("File");
        menu.setId("fileMenu");
        return menu;
    }

    public Menu createEditMenu() {
        Menu menu = new Menu();
        menu.setText("Edit");
        menu.setId("editMenu");
        return menu;
    }

    public Menu createSettingMenu() {
        Menu menu = new Menu();
        menu.setText("Setting");
        menu.setId("settingMenu");
        return menu;
    }

}
