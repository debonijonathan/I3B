package ch.supsi.bthread.view;

import javafx.beans.binding.DoubleBinding;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

public class TableViewSemaphoreFactory {
    private static TableViewSemaphoreFactory factory;

    protected TableViewSemaphoreFactory() {}

    public static TableViewSemaphoreFactory instance() {
        if (factory == null) {
            factory = new TableViewSemaphoreFactory();
        }
        return factory;
    }

    public TableView createTableView(Stage stage) {
        TableView tableView = new TableView();
        tableView.setEditable(false);
        DoubleBinding val = stage.widthProperty().divide(5);
        TableColumn memIdCol = new TableColumn("SemaphoreId");
        memIdCol.setCellValueFactory(new PropertyValueFactory<>("semaphoreId"));
        memIdCol.prefWidthProperty().bind(val.divide(100).multiply(30));
        TableColumn valueCol = new TableColumn("Value");
        valueCol.setCellValueFactory(new PropertyValueFactory<>("semaphoreValue"));
        valueCol.prefWidthProperty().bind(val.divide(100).multiply(30));
        TableColumn queueCol = new TableColumn("Queue");
        queueCol.setCellValueFactory(new PropertyValueFactory<>("queue"));
        queueCol.prefWidthProperty().bind(val.divide(100).multiply(30));
        tableView.getColumns().addAll(memIdCol,valueCol, queueCol);
        return tableView;
    }
}
