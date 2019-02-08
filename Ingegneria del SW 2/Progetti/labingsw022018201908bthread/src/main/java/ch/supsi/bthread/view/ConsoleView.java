package ch.supsi.bthread.view;

import javafx.application.Platform;
import javafx.scene.Node;
import javafx.scene.control.TextArea;
import ch.supsi.bthread.event.*;

import java.util.Observable;
import java.util.Observer;

public class ConsoleView implements Observer {

    protected static final int DEFAULT_TEXT_ROWS = 11;

    private TextArea console;

    public static ConsoleView create() {
        ConsoleView consoleView = new ConsoleView();
        consoleView.console = new TextArea();
        consoleView.console.setEditable(false);
        consoleView.console.setId("console");
        consoleView.console.setPrefRowCount(DEFAULT_TEXT_ROWS);
        return consoleView;
    }

    public Node getActualComponent() {
        return console;
    }

    public void changeStatusCommandLine(){
        if(console.isVisible()){
            console.setVisible(false);
        }else{
            console.setVisible(true);
        }
    }

    @Override
    public void update(Observable o, Object event) {
        new Thread(() -> Platform.runLater(()-> {
            if (event instanceof ProcessStartedEvent) {
                console.clear();
                console.appendText("process started..." + ((ProcessStartedEvent) event).getGetId() + "\n");

            } else if (event instanceof ProcessResumedEvent) {
                console.appendText("process resumed..." + ((ProcessResumedEvent) event).getGetId() + "\n");

            } else if (event instanceof ProcessNotStartedEvent) {
                console.appendText("process stopped..." + ((ProcessNotStartedEvent) event).getFilename() + "\n");

            } else if (event instanceof ProcessStoppedEvent) {
                console.appendText("process stopped..." + ((ProcessStoppedEvent) event).getId() + "\n");

            } else if (event instanceof ProcessPausedEvent) {
                console.appendText("process paused..." + ((ProcessPausedEvent) event).getId() + "\n");

            } else if (event instanceof NewLineReadEvent) {
                console.appendText(((NewLineReadEvent) event).getLine());

            } else if(event instanceof StatusCommandLineEvent) {

                if(console.isVisible()){
                    console.setVisible(false);
                }else{
                    console.setVisible(true);
                }
            }
        })
        ).start();

    }

}
