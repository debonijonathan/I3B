package ch.supsi.bthread.model;

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.concurrent.Task;
import ch.supsi.bthread.event.*;
import ch.supsi.bthread.iface.ExitManager;
import ch.supsi.bthread.iface.MonitoringManager;
import ch.supsi.bthread.iface.ProcessManager;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import javax.xml.crypto.Data;
import java.io.*;
import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Observable;
import java.util.regex.Matcher;
import java.util.regex.Pattern;



public class Model extends Observable implements ProcessManager, MonitoringManager, ExitManager {

    private static Model model;
    private Scheduler scheduler;
    private String executablePath;
    private String threadActive = null;
    private String log;
    protected Process process;
    protected String processId;

    protected Model() {}

    public static Model instance() {
        if (model == null) {
            model = new Model();
        }

        return model;
    }

    @Override
    public void playProcess(String path) {

        scheduler.clear();

        this.executablePath = path;

        // Resume command
        if (process != null) {
            /* Process is alive */

            String line = getPid();

            runCommand("kill -SIGCONT "+ line);

            this.setChanged();
            this.notifyObservers(new ProcessResumedEvent(processId));
            return;
        }

        // create new process
        try {
            ProcessBuilder processBuilder = new ProcessBuilder(executablePath);
            processBuilder.redirectErrorStream(true);
            process = processBuilder.start();
            processId = process.toString();
            redirectionOutput();
            this.setChanged();
            this.notifyObservers(new ProcessStartedEvent(processId));

        } catch (IOException e) {
            e.printStackTrace();
            this.setChanged();
            this.notifyObservers(new ProcessNotStartedEvent(executablePath));
        }
    }

    private String getPid() {
        String[] splitted = executablePath.split("/");
        String filename = splitted[splitted.length - 1];

        String line = "";
        Process p;
        try {
            p = Runtime.getRuntime().exec("pidof " + filename);
            p.waitFor();
            BufferedReader reader =
                    new BufferedReader(new InputStreamReader(p.getInputStream()));
            line = reader.readLine();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return line;
    }

    @Override
    public void stopProcess() {
        if (process == null) {
            return;
        }

        threadActive = null;
        process.destroyForcibly();
        process = null;

        this.setChanged();
        this.notifyObservers(new ProcessStoppedEvent(processId));
    }

    @Override
    public void pauseProcess() {
        if (process == null) {
            return;
        }

        String line = getPid();

        runCommand("kill -SIGSTOP "+line);

        this.setChanged();
        this.notifyObservers(new ProcessPausedEvent(processId));
    }

    private void runCommand(String command) {
        Process p1;
        try {
            p1 = Runtime.getRuntime().exec(command);
            p1.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void setScheduler(Scheduler scheduler) {
        this.scheduler = scheduler;
    }

    private void redirectionOutput(){
        if (process == null) {
            return;
        }

        Task<Void> task = new Task<Void>() {
            @Override
            protected Void call() throws Exception {
                String pattern = "(((\\S+BLOCKED)|(\\S+WAIT))(?:\\S+ ){4}(\\S+))|(((\\S+ACQUIRE)|(\\S+RELEASE)|(\\S+WAIT)|(\\S+POST)|(\\S+UNLOCK)|(\\S+EXIT)|(\\S+DESTROY))(?:\\S+ ){3}(\\S+))|(((\\S+ACQUIRE)|(\\S+RELEASE)|(\\S+WAIT)|(\\S+POST)|(\\S+SIGNAL)|(\\S+BROADCAST)|(\\S+BLOCKED)|(\\S+FAIL))(?:\\S+ ){2}(\\S+))|((\\S+BLOCKED)|(\\S+CREATE)|(\\S+YIELD))(?:\\S+ ){1}(\\S+)";

                InputStream processStdOut = process.getInputStream();
                InputStreamReader isr = new InputStreamReader(processStdOut);
                BufferedReader br = new BufferedReader(isr);
                String line;
                String[] parameters;

                while (process.isAlive()) {
                    line = br.readLine();

                    /*Qua ho modificato*/
                    Pattern r = Pattern.compile(pattern);
                    Matcher m = r.matcher(line);
                    if(m.find()) {

                        //ContainerParser parsed = parseSingleData(m.group());
                        parameters = m.group().split(" ");
                        parse(parameters);
                    }

                    if(threadActive!=null){
                        setChanged();
                        notifyObservers(new GanttStatusEvent(threadActive));
                    }

                    if (line != null) {
                        updateMessage(line);
                        addToLog(line);
                    }

                }
                return null;
            }
        };

        task.messageProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) {
                setChanged();
                notifyObservers(new NewLineReadEvent(newValue + "\n"));
            }
        });

        new Thread(task).start();

        setChanged();
        notifyObservers(new MonitoringStartedEvent());
    }

    private void parse(String[] parameters) {
        if(!parameters[0].equals(""))
        switch (replaceBrackets(parameters[0]).substring(0, 3)) {
            case "SEM":
                if (parameters.length == 4){
                    scheduler.addSemaphore(new Semaphore(parameters[0], parameters[2], parameters[3]), parameters[1]);
                }else
                    scheduler.changeThreadStatus(parameters[1], "BLOCKED");
                break;
            case "MUT":
                if (parameters.length == 3){
                    scheduler.addMutex(new Mutex(parameters[0], parameters[2]), parameters[1]);
                }
                break;
            case "BAR":
                if (parameters.length == 5)
                    scheduler.addBarrier(new Barrier(parameters[0], parameters[2], parameters[3], parameters[4]), parameters[1]);
                else
                    scheduler.getBarriers().get(parameters[1]).getQueue().clear();
                break;
            case "CON":
                if(parameters.length != 2)
                    scheduler.addConditionVariables(new ConditionVariable(parameters[0], parameters[2]),parameters[1]);
                else {
                    scheduler.changeThreadStatus(parameters[1], "BLOCKED");
                }
                break;
            case "YIE":
                threadActive = parameters[1];
                break;
            case "CRE":
                scheduler.addThread(new ThreadS(parameters[1], "READY"),parameters[1]);
                setChanged();
                notifyObservers(new GanttCreateThreadEvent(parameters[1]));
                break;
            case "REA":
                scheduler.addThread(new ThreadS(parameters[1], "READY"),parameters[1]);
            case "SLE":
                scheduler.changeThreadStatus(parameters[1], "SLEEPING");
                break;
            case "EXI":
                scheduler.changeThreadStatus(parameters[1], "ZOMBIE");
                break;
            case "DES":
                scheduler.getThreadStatus().remove(parameters[1]);
            default:
                break;

        }
    }

    String replaceBrackets(String value){
        String tmp = value.replace("(","");
        return tmp.replace(")","");
    }

    @Override
    public void exportLog() {
        System.out.println("exportlog...");
        FileOutputStream fos = null;
        try {
            fos = new FileOutputStream("log.txt");
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        if (fos != null){
            log.replaceAll("null", "");
            byte[] dataToWrite = log.getBytes();
            try {
                fos.write(dataToWrite);
            } catch (IOException e) {
                e.printStackTrace();
            }
            System.out.println("log exported");
        }
        try {
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void exit() {
        System.exit(0);
    }

    private void addToLog(String text){
        log += text;
        log += "\n";
    }
}
