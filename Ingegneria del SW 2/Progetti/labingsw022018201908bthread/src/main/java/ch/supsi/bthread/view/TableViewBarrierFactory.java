package ch.supsi.bthread.view;

import javafx.beans.binding.DoubleBinding;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

public class TableViewBarrierFactory {
    private static TableViewBarrierFactory factory;

    protected TableViewBarrierFactory() {}

    public static TableViewBarrierFactory instance() {
        if (factory == null) {
            factory = new TableViewBarrierFactory();
        }
        return factory;
    }

    public TableView createTableView(Stage stage) {
        TableView tableView = new TableView();
        tableView.setEditable(false);
        DoubleBinding val = stage.widthProperty().divide(5);
        TableColumn memIdCol = new TableColumn("MemId");
        memIdCol.setCellValueFactory(new PropertyValueFactory<>("barrierId"));
        memIdCol.prefWidthProperty().bind(val.divide(100).multiply(30));
        TableColumn queueCol = new TableColumn("Queue");
        queueCol.setCellValueFactory(new PropertyValueFactory<>("queue"));
        queueCol.prefWidthProperty().bind(val.divide(100).multiply(30));
        TableColumn dimCol = new TableColumn("Dimension");
        dimCol.setCellValueFactory(new PropertyValueFactory<>("barrierSize"));
        dimCol.prefWidthProperty().bind(val.divide(100).multiply(30));
        tableView.getColumns().addAll(memIdCol,queueCol, dimCol);
        return tableView;


    }

}
