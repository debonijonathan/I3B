package ch.supsi.bthread.view;

import java.io.File;
import java.net.URL;
import java.util.ArrayList;
import java.util.Observable;
import java.util.Observer;

import ch.supsi.bthread.command.StopProcessCommand;
import ch.supsi.bthread.event.*;
import ch.supsi.bthread.model.GanttChart;
import ch.supsi.bthread.model.GanttChart.ExtraData;

import java.util.Arrays;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.Scene;
import javafx.scene.chart.Axis;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

public class GanttChartView implements Observer {

    private GanttChart<Number, String> chart;
    private static GanttChartView ganttChartView;
    private static ArrayList<String> labels;
    private static ArrayList<XYChart.Series> series;
    static int last_value_x = 0;
    final static NumberAxis xAxis = new NumberAxis();


    public static GanttChartView create() {

        labels = new ArrayList<>();
        series = new ArrayList<>();
        final CategoryAxis yAxis = new CategoryAxis();

        ganttChartView = new GanttChartView();
        ganttChartView.chart = new GanttChart<Number, String>(xAxis, yAxis);
        ganttChartView.chart.setId("gantt");

        xAxis.setLabel("Time");
        xAxis.setTickLabelFill(Color.CHOCOLATE);
        xAxis.setMinorTickCount(1);
        xAxis.setForceZeroInRange(false);

        yAxis.setLabel("Threads");
        yAxis.setTickLabelFill(Color.CHOCOLATE);
        yAxis.setTickLabelGap(10);
        yAxis.setCategories(FXCollections.<String>observableArrayList(labels));
        yAxis.setAutoRanging(false);

        ganttChartView.chart.setLegendVisible(false);
        ganttChartView.chart.setBlockHeight(30);
        ganttChartView.chart.getStylesheets().add("ganttchart.css");

        return ganttChartView;
    }

    public GanttChart getActualComponent() {
        return chart;
    }

    @Override
    public void update(Observable o, Object event) {

        if (event instanceof GanttCreateThreadEvent) {

            String v = ((GanttCreateThreadEvent) event).getThreadId();
            int id = Integer.parseInt(v);

            Platform.runLater(new Runnable() {

                @Override
                public void run() {
                    if (!labels.contains(v)) {
                        labels.add(id - 1, "Thread " + id);
                        series.add(id - 1, new XYChart.Series());
                        CategoryAxis yAxis = (CategoryAxis) ganttChartView.chart.getYAxis();
                        ObservableList<String> categories = yAxis.getCategories();
                        categories.add(labels.get(id - 1));
                        yAxis.setCategories(categories);
                        last_value_x += 1;
                        ganttChartView.chart.getData().add(series.get(id - 1));
                        System.out.println("Thread " + ((GanttCreateThreadEvent) event).getThreadId() + " creato.");
                    }
                }
            });


        } else if (event instanceof GanttStatusEvent) {
            String v = ((GanttStatusEvent) event).getGetId();
            int id = Integer.parseInt(v);

            Platform.runLater(new Runnable() {

                @Override
                public void run() {
                    if (!labels.contains(v))
                        labels.add(id, "Thread " + id);

                    last_value_x += 1;

                    series.add(id, new XYChart.Series());
                    series.get(id).getData().add(new XYChart.Data(last_value_x, labels.get(id), new ExtraData(1, "status-blue")));
                    ganttChartView.chart.getData().add(series.get(id));

                    if (ganttChartView.chart.getData().size() > 200) {
                        ganttChartView.chart.getData().remove(0);
                    }
                }
            });
            try {
                Thread.sleep(1);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        } else if (event instanceof ProcessStartedEvent) {
            clearStructures();
            last_value_x = 0;
        } else if (event instanceof ProcessLoadedEvent){
        }

    }

    private void clearStructures() {
        series.clear();
        labels.clear();
        CategoryAxis yAxis = (CategoryAxis) ganttChartView.chart.getYAxis();
        yAxis.getCategories().clear();
        ganttChartView.chart.getData().removeAll(ganttChartView.chart.getData());
    }
}
