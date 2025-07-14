package visulization.component;

import data.Observer;
import visulization.MenuFrame;

import javax.swing.*;

public class CodEdit extends JTextArea implements Observer {

    @Override
    public void upData() {
        setDocument(MenuFrame.project.getActiveClass());
        setTabSize(5);
    }

}
