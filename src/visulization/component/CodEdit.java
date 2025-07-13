package visulization.component;

import data.Observer;
import visulization.MenuFrame;

import javax.swing.*;

public class CodEdit extends JTextArea implements Observer {

    public CodEdit(){
        setTabSize(5);
    }

    @Override
    public void upData() {
        setDocument(MenuFrame.project.getActiveClass());
    }

}
