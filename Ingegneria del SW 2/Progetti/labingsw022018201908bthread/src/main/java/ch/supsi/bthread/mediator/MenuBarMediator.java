package ch.supsi.bthread.mediator;

import ch.supsi.bthread.command.PlayProcessCommand;
import ch.supsi.bthread.event.*;
import ch.supsi.bthread.model.Model;
import ch.supsi.bthread.view.MyMenuItem;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.awt.*;
import java.util.Observable;
import java.util.Observer;

public class MenuBarMediator implements Observer {

    private MyMenuItem playMenuItem;
    private MyMenuItem stopMenuItem;
    private MyMenuItem pauseMenuItem;

    private PlayProcessCommand playProcessCommand;

    private MenuBarMediator() {}

    public static MenuBarMediator create() {
        MenuBarMediator menuBarMediator = new MenuBarMediator();
        return menuBarMediator;
    }

    public void setPlayMenuItem(MyMenuItem playMenuItem) {
        this.playMenuItem = playMenuItem;
    }

    public void setStopMenuItem(MyMenuItem stopMenuItem) {
        this.stopMenuItem = stopMenuItem;
    }

    public void setPauseMenuItem(MyMenuItem pauseMenuItem) {
        this.pauseMenuItem = pauseMenuItem;
    }

    public void setPlayProcessCommand(PlayProcessCommand playProcessCommand) { this.playProcessCommand = playProcessCommand; }

    public MyMenuItem getPlayMenuItem() {
        return  playMenuItem;
    }

    public MyMenuItem getStopMenuItem() {
        return stopMenuItem;
    }

    public MyMenuItem getPauseMenuItem() {
        return pauseMenuItem;
    }

    public PlayProcessCommand getPlayProcessCommand() {
        return playProcessCommand;
    }

    public void openPath(){
        FileChooser fileChooser = new FileChooser();
        fileChooser = new FileChooser();
        fileChooser.setTitle("Open Resource File");
        fileChooser.getExtensionFilters().addAll(
                new FileChooser.ExtensionFilter("All Files", "*"));
        try{
            String path = fileChooser.showOpenDialog(new Stage()).getAbsolutePath();
            this.playProcessCommand.setPath(path);

            playMenuItem.enable();
            stopMenuItem.disable();
            pauseMenuItem.disable();

        }catch (NullPointerException e){
        }
    }

    @Override
    public void update(Observable o, Object event) {

        if (event instanceof ProcessStartedEvent || event instanceof ProcessResumedEvent) {
            playMenuItem.disable();
            stopMenuItem.enable();
            pauseMenuItem.enable();

        } else if (event instanceof ProcessStoppedEvent) {
            playMenuItem.getActualComponent().setText("Play");
            playMenuItem.enable();
            stopMenuItem.disable();
            pauseMenuItem.disable();

        } else if (event instanceof ProcessPausedEvent){
            playMenuItem.getActualComponent().setText("Resume");
            playMenuItem.enable();
            stopMenuItem.disable();
            pauseMenuItem.disable();
        }
    }

}
