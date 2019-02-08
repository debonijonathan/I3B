package ch.supsi.bthread;
import ch.supsi.bthread.mediator.TableViewMediator;
import ch.supsi.bthread.model.Scheduler;
import ch.supsi.bthread.view.MenuItemsFactory;
import ch.supsi.bthread.view.MenusFactory;
import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.chart.*;
import javafx.scene.control.*;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import ch.supsi.bthread.command.*;
import ch.supsi.bthread.controller.ExitController;
import ch.supsi.bthread.controller.MonitoringController;
import ch.supsi.bthread.controller.ProcessController;
import ch.supsi.bthread.mediator.MenuBarMediator;
import ch.supsi.bthread.model.Model;
import ch.supsi.bthread.view.*;
import java.io.FileNotFoundException;

public class Main extends Application{
    private MenuBar menuBar;
    private Model model;
    private ConsoleView consoleView;
    private Scheduler scheduler;
//    private MyTableView myTableView;
    private ProcessController processController;
    private MonitoringController monitoringController;
    private ExitController exitController;
    private MenuBarMediator menuBarMediator;
    private TableViewMediator tableViewMediator;
    private GanttChartView ganttChartView;

    MenuBar getMenuBar(){
        return menuBar;
    }
    public Main() {
        // model(s)
        model = Model.instance();
        // view(s)
        consoleView = ConsoleView.create();
        ganttChartView = GanttChartView.create();
        // controller(s)
        processController = ProcessController.create(model);
        monitoringController = MonitoringController.create(model);
        exitController = ExitController.create(model);
        // mediator create
        menuBarMediator = MenuBarMediator.create();
        tableViewMediator = TableViewMediator.create();
        // FILE MENU
        MyMenuItem openMenuItem = MenuItemsFactory.instance().createOpenMenuItem(OpenFileCommand.create(menuBarMediator));
        openMenuItem.setId("openMenuItem");
        MyMenuItem exitMenuItem = MenuItemsFactory.instance().createExitMenuItem(ExitCommand.create(exitController));
        exitMenuItem.setId("exitMenuItem");

        Menu fileMenu = MenusFactory.instance().createFileMenu();
        fileMenu.setId("fileMenu");
        fileMenu.getItems().add(openMenuItem.getActualComponent());
        fileMenu.getItems().add(exitMenuItem.getActualComponent());
        // EDIT MENU
        PlayProcessCommand playProcessCommand = PlayProcessCommand.create(processController);
        MyMenuItem startProcessMenuItem = MenuItemsFactory.instance().createPlayMenuItem(playProcessCommand);
        MyMenuItem pauseProcessMenuItem = MenuItemsFactory.instance().createPauseMenuItem(PauseProcessCommand.create(processController));
        MyMenuItem stopProcessMenuItem = MenuItemsFactory.instance().createStopMenuItem(StopProcessCommand.create(processController));
        //MyMenuItem startMonitoringMenuItem = MenuItemsFactory.instance().createStartMonitoringItem(StartMonitoringCommand.create(monitoringController));
        Menu editMenu = MenusFactory.instance().createEditMenu();
        editMenu.setId("editMenu");
        startProcessMenuItem.setId("startProcessMenuItem");
        pauseProcessMenuItem.setId("pauseProcessMenuItem");
        stopProcessMenuItem.setId("stopProcessMenuItem");

        editMenu.getItems().add(startProcessMenuItem.getActualComponent());
        editMenu.getItems().add(pauseProcessMenuItem.getActualComponent());
        editMenu.getItems().add(stopProcessMenuItem.getActualComponent());
        /* Tolgo momentaneamente il pulsante Start Monitoring */
        //editMenu.getItems().add(new SeparatorMenuItem());
        //editMenu.getItems().add(startMonitoringMenuItem.getActualComponent());
        // SETTING MENU
        //MyMenuItem tracingMenuItem = MenuItemsFactory.instance().createTracingMenuItem(StartMonitoringCommand.create(monitoringController));
        MyMenuItem exportLogMenuItem = MenuItemsFactory.instance().createExportLogMenuItem(ExportCommand.create(monitoringController));
        MyRadioItem commandLineMenuItem = MenuItemsFactory.instance().createShowMenuItem(ShowCommand.create(consoleView));
        exportLogMenuItem.setId("exportLogMenuItem");
        commandLineMenuItem.setId("commandLineMenuItem");
        Menu settingMenu = MenusFactory.instance().createSettingMenu();
        settingMenu.setId("settingMenu");
//        settingMenu.getItems().add(tracingMenuItem.getActualComponent());
        settingMenu.getItems().add(commandLineMenuItem.getActualComponent());
        settingMenu.getItems().add(exportLogMenuItem.getActualComponent());
        // MENU BAR
        menuBar = new MenuBar();
        menuBar.setId("menuBar");
        menuBar.getMenus().addAll(fileMenu, editMenu, settingMenu);
        System.out.println(settingMenu.getItems());
        // mediator(s)
        menuBarMediator.setPlayMenuItem(startProcessMenuItem);
        menuBarMediator.setStopMenuItem(stopProcessMenuItem);
        menuBarMediator.setPauseMenuItem(pauseProcessMenuItem);
//        menuBarMediator.setStartMonitoringMenuItem(tracingMenuItem);
        menuBarMediator.setPlayProcessCommand(playProcessCommand);
        // observer(s)
        model.addObserver(consoleView);
        model.addObserver(menuBarMediator);
        model.addObserver(ganttChartView);
        model.addObserver(tableViewMediator);
        scheduler.instance().addObserver(tableViewMediator);
        // starting defaults
        startProcessMenuItem.disable();
        pauseProcessMenuItem.disable();
        stopProcessMenuItem.disable();
//        tracingMenuItem.disable();
    }
    /*PieChart chartPie(Stage stage){
        ObservableList<PieChart.Data> pieChartData =
                FXCollections.observableArrayList(
                        new PieChart.Data("Thread1", 13),
                        new PieChart.Data("Thread2", 25),
                        new PieChart.Data("Thread3", 10),
                        new PieChart.Data("Thread4", 22),
                        new PieChart.Data("Thread5", 30));
        final PieChart chart = new PieChart(pieChartData);
        chart.setTitle("Memory");
        chart.prefWidthProperty().bind(stage.widthProperty().divide(3));
        chart.prefHeightProperty().bind(stage.heightProperty().divide(3));
        return chart;
    }*/

    private TableView tableCol(Stage stage){
        TableView table = new TableView();
        table.setEditable(false);

        TableColumn typeCol = new TableColumn("Tipo");
        typeCol.prefWidthProperty().bind(stage.widthProperty().divide(3));
        TableColumn valueCol = new TableColumn("Valore");
        valueCol.prefWidthProperty().bind(table.widthProperty().divide(1.6));

        table.getColumns().addAll(typeCol,valueCol);
        return table;
    }

    @Override
    public void start(Stage stage) throws FileNotFoundException {
        /* Setting default information */
        stage.setTitle("Bthread Reader");
        stage.setMinHeight(1000);
        stage.setMaxHeight(1000);
        stage.setMinWidth(1250);
        stage.setMaxWidth(1250);

        BorderPane borderPane = new BorderPane();
        borderPane.setId("borderPane");

        BorderPane borderPane2 = new BorderPane();
        borderPane2.setId("borderPane2");

        GridPane gridPane = new GridPane();
        gridPane.setId("gridPane");

        Group root = new Group();
        Scene scene = new Scene(root);


        //TableView table = tableCol(stage);
        //table.prefWidthProperty().bind(stage.widthProperty());

//        myTableView = MyTableView.create(stage);
//        model.addObserver(myTableView);

        TableView tableViewMutex = TableViewMutexFactory.instance().createTableView(stage);
        TableView tableViewSemaphore = TableViewSemaphoreFactory.instance().createTableView(stage);
        TableView tableViewBarrier = TableViewBarrierFactory.instance().createTableView(stage);
        TableView tableViewCondVar = TableViewConditionVariableFactory.instance().createTableView(stage);
        TableView tableViewStatus = TableViewThreadStatusFactory.instance().createTableView(stage);
        tableViewMediator.setTableViewMutex(tableViewMutex);
        tableViewMediator.tableViewMutex.setId("tableViewMutex");
        tableViewMediator.setTableViewSamaphore(tableViewSemaphore);
        tableViewMediator.tableViewSamaphore.setId("tableViewSamaphore");
        tableViewMediator.setTableViewBarrier(tableViewBarrier);
        tableViewMediator.tableViewBarrier.setId("tableViewBarrier");
        tableViewMediator.setTableViewCondVar(tableViewCondVar);
        tableViewMediator.tableViewCondVar.setId("tableViewCondVar");
        tableViewMediator.setTableViewThreadStatus(tableViewStatus);
        tableViewMediator.tableViewThreadStatus.setId("tableViewThreadStatus");
        tableViewMediator.setScheduler(scheduler.instance());
        model.setScheduler(scheduler.instance());
        menuBar.prefWidthProperty().bind(stage.widthProperty());
        gridPane.add(tableViewMutex,0,0);
        gridPane.add(tableViewBarrier,1,0);
        gridPane.add(tableViewCondVar,2,0);
        gridPane.add(tableViewStatus,3,0);
        gridPane.add(tableViewSemaphore,4,0);
        borderPane.setTop(menuBar);
        borderPane2.setTop(gridPane);
        borderPane2.setCenter(ganttChartView.getActualComponent());
        borderPane.setCenter(borderPane2);
        borderPane.setBottom(consoleView.getActualComponent());
        root.getChildren().addAll(borderPane);

        stage.setScene(scene);
        stage.show();
    }
    public static void main(String[] args) {
        launch(args);
    }
}