package ch.supsi.bthread.view;

import javafx.beans.binding.DoubleBinding;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

public class TableViewConditionVariableFactory {
    private static TableViewConditionVariableFactory factory;

    protected TableViewConditionVariableFactory() {}

    public static TableViewConditionVariableFactory instance() {
        if (factory == null) {
            factory = new TableViewConditionVariableFactory();
        }
        return factory;
    }

    public TableView createTableView(Stage stage) {
        TableView tableView = new TableView();
        tableView.setEditable(false);
        DoubleBinding val = stage.widthProperty().divide(5);
        TableColumn memidCol = new TableColumn("variableId");
        memidCol.setCellValueFactory(new PropertyValueFactory<>("variableId"));
        memidCol.prefWidthProperty().bind(val.divide(100).multiply(45));
        TableColumn queueCol = new TableColumn("Queue");
        queueCol.setCellValueFactory(new PropertyValueFactory<>("queue"));
        queueCol.prefWidthProperty().bind(val.divide(100).multiply(45));
        tableView.getColumns().addAll(memidCol,queueCol);
        return tableView;

    }
}
