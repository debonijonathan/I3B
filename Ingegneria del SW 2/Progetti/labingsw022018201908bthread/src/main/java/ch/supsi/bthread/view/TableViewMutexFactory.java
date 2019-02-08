package ch.supsi.bthread.view;

import ch.supsi.bthread.model.Barrier;
import javafx.beans.binding.DoubleBinding;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

public class TableViewMutexFactory {
    private static TableViewMutexFactory factory;

    protected TableViewMutexFactory() {}

    public static TableViewMutexFactory instance() {
        if (factory == null) {
            factory = new TableViewMutexFactory();
        }
        return factory;
    }

    public TableView createTableView(Stage stage) {
        TableView tableView = new TableView();
        tableView.setEditable(false);
        DoubleBinding val = stage.widthProperty().divide(5);
        TableColumn memIdCol = new TableColumn("MutexId");
        memIdCol.setCellValueFactory(new PropertyValueFactory<>("mutexId"));
        memIdCol.prefWidthProperty().bind(val.divide(100).multiply(30));
        TableColumn ownerCol = new TableColumn("Owner");
        ownerCol.setCellValueFactory(new PropertyValueFactory<>("owner"));
        ownerCol.prefWidthProperty().bind(val.divide(100).multiply(30));
        TableColumn queueCol = new TableColumn("Queue");
        queueCol.setCellValueFactory(new PropertyValueFactory<>("queue"));
        queueCol.prefWidthProperty().bind(val.divide(100).multiply(30));
        tableView.getColumns().addAll(memIdCol,ownerCol, queueCol);

        return tableView;

    }
}
