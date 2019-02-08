package ch.supsi.bthread;

import ch.supsi.bthread.view.MyMenuItem;
import javafx.scene.Node;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuBar;
import javafx.stage.Stage;
import org.junit.Assert;
import org.junit.Ignore;
import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.testfx.framework.junit.ApplicationTest;

import static org.junit.Assert.*;

import static org.testfx.api.FxAssert.verifyThat;
import static org.testfx.matcher.base.NodeMatchers.*;

public class MainTest extends ApplicationTest {

    private static final Logger LOGGER = LoggerFactory.getLogger(MainTest.class);

    private static final int ACTIONS_INTERVAL = 0;

    private int stepNo;

    private MenuBar menuBar;

    @Override
    public void start(Stage stage) throws Exception {
        Main main = new Main();
        menuBar = main.getMenuBar();
        main.start(stage);
    }

    @Test
    public void componentsWalkThrough01(){
        step("Components", () -> {
            verifyThat("#menuBar", isVisible());
            verifyThat("#borderPane", Node::isVisible);
            verifyThat("#borderPane2", isVisible());
            verifyThat("#gridPane", isVisible());
            verifyThat("#console", isVisible());
            verifyThat("#tableViewMutex", isVisible());
            verifyThat("#tableViewSamaphore", isVisible());
            verifyThat("#tableViewBarrier", isVisible());
            verifyThat("#tableViewCondVar", isVisible());
            verifyThat("#tableViewThreadStatus", isVisible());
            verifyThat("#gantt",isVisible());
        });
    }

    @Ignore
    public void menuBarWalkThrough01(){
        step("File menu", () -> {
            sleep(ACTIONS_INTERVAL);
            verifyThat("#fileMenu",isVisible());
            clickOn("#fileMenu");
            verifyThat("#openMenuItem", isVisible());
            verifyThat("#exitMenuItem", isVisible());


        });

        step("Edit menu", () -> {
            sleep(ACTIONS_INTERVAL);
            clickOn("#editMenu");
            verifyThat("#startProcessMenuItem", isDisabled());
            verifyThat("#pauseProcessMenuItem", isVisible());
            verifyThat("#stopProcessMenuItem", isVisible());

        });


        step("Setting menu", () -> {
            sleep(ACTIONS_INTERVAL);
            clickOn("#settingMenu");
            verifyThat("#exportLogMenuItem", isVisible());
            verifyThat("#commandLineMenuItem", isVisible());

            sleep(ACTIONS_INTERVAL);
            clickOn("#commandLineMenuItem");
            verifyThat("#console", isInvisible());
        });
    }


    private void step(final String step, final Runnable runnable) {
        ++stepNo;
        LOGGER.info("STEP {}: {}", stepNo, step);
        runnable.run();
        LOGGER.info("STEP {}: End", stepNo);
    }
}