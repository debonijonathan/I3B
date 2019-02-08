package ch.supsi.bthread.view;

import javafx.beans.binding.DoubleBinding;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

public class TableViewThreadStatusFactory {
    private static TableViewThreadStatusFactory factory;

    protected TableViewThreadStatusFactory() {}

    public static TableViewThreadStatusFactory instance() {
        if (factory == null) {
            factory = new TableViewThreadStatusFactory();
        }
        return factory;
    }

    public TableView createTableView(Stage stage) {
        TableView tableView = new TableView();
        tableView.setEditable(false);
        DoubleBinding val = stage.widthProperty().divide(5);
        TableColumn threadCol = new TableColumn("Thread");
        threadCol.setCellValueFactory(new PropertyValueFactory<>("threadId"));
        threadCol.prefWidthProperty().bind(val.divide(100).multiply(45));
        TableColumn statusCol = new TableColumn("Status");
        statusCol.setCellValueFactory(new PropertyValueFactory<>("status"));
        statusCol.prefWidthProperty().bind(val.divide(100).multiply(45));
        tableView.getColumns().addAll(threadCol,statusCol);

        return tableView;


    }
}
