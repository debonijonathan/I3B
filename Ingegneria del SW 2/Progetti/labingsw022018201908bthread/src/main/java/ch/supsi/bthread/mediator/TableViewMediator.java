package ch.supsi.bthread.mediator;

import ch.supsi.bthread.event.*;
import ch.supsi.bthread.model.*;
//import ch.supsi.bthread.view.MyTableView;
import javafx.application.Platform;
import javafx.scene.control.TableView;

import java.util.Observable;
import java.util.Observer;

public class TableViewMediator implements Observer {

    public TableView tableViewMutex;
    public TableView tableViewSamaphore;
    public TableView tableViewBarrier;
    public TableView tableViewCondVar;
    public TableView tableViewThreadStatus;

    private Scheduler scheduler;

    private TableViewMediator(){}

    public static TableViewMediator create(){
        TableViewMediator tableViewMediator = new TableViewMediator();
        return tableViewMediator;
    }

    public void setTableViewMutex(TableView tableViewMutex) {
        this.tableViewMutex = tableViewMutex;
    }

    public void setTableViewSamaphore(TableView tableViewSamaphore) {
        this.tableViewSamaphore = tableViewSamaphore;
    }

    public void setTableViewBarrier(TableView tableViewBarrier) {
        this.tableViewBarrier = tableViewBarrier;
    }

    public void setTableViewCondVar(TableView tableViewCondVar) {
        this.tableViewCondVar = tableViewCondVar;
    }

    public void setTableViewThreadStatus(TableView tableViewThreadStatus) { this.tableViewThreadStatus = tableViewThreadStatus; }

    public void setScheduler(Scheduler scheduler) { this.scheduler = scheduler; }

    public TableView getTableViewMutex() {
        return tableViewMutex;
    }

    public TableView getTableViewSamaphore() {
        return tableViewSamaphore;
    }

    public TableView getTableViewBarrier() {
        return tableViewBarrier;
    }

    public TableView getTableViewCondVar() {
        return tableViewCondVar;
    }

    public TableView getTableViewThreadStatus() {
        return tableViewThreadStatus;
    }

    public Scheduler getScheduler() {
        return scheduler;
    }

    @Override
    public void update(Observable observable, Object event) {

        if(event instanceof NewRowSemaphore){
            Platform.runLater(new Runnable() {
                @Override public void run() {
                    tableViewSamaphore.getItems().clear();
                    for (String key : scheduler.getSemaphores().keySet()) {
                        Semaphore semaphore = scheduler.getSemaphores().get(key);
                        tableViewSamaphore.getItems().addAll(semaphore);
                    }
                }});
        }else if(event instanceof  NewRowBarrier){
            Platform.runLater(new Runnable() {
                @Override public void run() {
                    tableViewBarrier.getItems().clear();
                    for (String key : scheduler.getBarriers().keySet()) {
                        Barrier barrier = scheduler.getBarriers().get(key);
                        tableViewSamaphore.getItems().addAll(barrier);
                    }
                }});
        }else if(event instanceof NewRowMutex){
            Platform.runLater(new Runnable() {
                @Override public void run() {
                    tableViewMutex.getItems().clear();
                    for (String key : scheduler.getMutexes().keySet()) {
                        Mutex mutex = scheduler.getMutexes().get(key);
                        tableViewMutex.getItems().addAll(mutex);
                    }
                }});
        }else if(event instanceof NewRowCondVar){
            Platform.runLater(new Runnable() {
                @Override public void run() {
                    tableViewCondVar.getItems().clear();
                    for (String key : scheduler.getConditionVariables().keySet()) {
                        ConditionVariable cv = scheduler.getConditionVariables().get(key);
                        tableViewCondVar.getItems().addAll(cv);
                    }
                }});
        }else if(event instanceof NewRowThreadStatus){
            Platform.runLater(new Runnable() {
                @Override public void run() {
                    tableViewThreadStatus.getItems().clear();
                    for (String key : scheduler.getThreadStatus().keySet()) {
                        ThreadS threadS = scheduler.getThreadStatus().get(key);
                        tableViewThreadStatus.getItems().addAll(threadS);
                    }
                }});
        } else if (event instanceof ProcessStartedEvent) {
            Platform.runLater(new Runnable() {
                @Override
                public void run() {
                    tableViewBarrier.getItems().clear();
                    tableViewCondVar.getItems().clear();
                    tableViewMutex.getItems().clear();
                    tableViewSamaphore.getItems().clear();
                    tableViewThreadStatus.getItems().clear();
                }
            });

        }
    }
}
