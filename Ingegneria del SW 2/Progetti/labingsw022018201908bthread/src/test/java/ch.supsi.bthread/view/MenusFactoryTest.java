package ch.supsi.bthread.view;

import javafx.scene.control.Menu;
import org.junit.Test;

import static junit.framework.TestCase.assertTrue;

public class MenusFactoryTest {

    @Test
    public void instanceTest(){
        assertTrue(MenusFactory.instance() instanceof MenusFactory);
    }

    @Test
    public void createFileMenuTest(){
        assertTrue(MenusFactory.instance().createFileMenu() instanceof Menu);
    }

    @Test
    public void createEditMenuTest(){
        assertTrue(MenusFactory.instance().createEditMenu() instanceof Menu);
    }

    @Test
    public void createSettingMenuTest(){
        assertTrue(MenusFactory.instance().createSettingMenu() instanceof Menu);
    }
}
