package visulization.component;

import data.Observable;
import data.Observer;
import edit.JavaClassDocument;
import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.io.*;
import java.util.*;
import java.util.List;

public class PathPanel extends JPanel implements Observable{

    private JavaClassDocument activeClass = null;
    private final List<Observer> observerList = new ArrayList<>();

    public PathPanel(JavaClassDocument[] documents, String project) {
        setLayout(new FlowLayout(FlowLayout.LEFT));
        CatalogProject catalog = new CatalogProject();
        for (JavaClassDocument s : documents) {
            catalog.add(project + "/src", s);
        }
        add(catalog.data);
    }

    @Override
    public void addObserver(Observer observer) {
        observerList.add(observer);
    }

    @Override
    public void notifyObservers() {
        for (Observer d : observerList){
            d.upData();
        }
    }

    @Override
    public void removeObserver(Observer observer) {
        observerList.remove(observer);
    }

    private static class Elements extends JPanel{

        private static final int d = 35;
        protected final JLabel ICON;
        protected final JLabel NAME;

        public Elements(ImageIcon icon, String name){
            setLayout(new FlowLayout(FlowLayout.LEFT));
            BufferedImage bufferedImage = new BufferedImage(d, d,BufferedImage.TYPE_INT_ARGB);
            Graphics2D g2 = bufferedImage.createGraphics();
            g2.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BILINEAR);
            g2.drawImage(icon.getImage(), 0, 0, d, d, null);
            g2.dispose();
            ICON = new JLabel(new ImageIcon(bufferedImage));
            NAME = new JLabel(name);
            NAME.setFont(new Font(name, Font.BOLD, 15));
            add(ICON);
            add(NAME);
        }

    }

    public JavaClassDocument getActiveClass() {
        return activeClass;
    }

    private class ClassElements extends Elements {

        private static final ImageIcon MAIN_CLASS = new ImageIcon("./system/icon/main_class.png");
        private static final ImageIcon JAVA_CLASS = new ImageIcon("./system/icon/java_class.png");

        public ClassElements(JavaClassDocument file) {
            super(file.isMainClass() ? MAIN_CLASS : JAVA_CLASS, file.getName());
            NAME.setForeground(file.getTypeJavaClass().COLOR);
            addMouseListener(new MouseListener() {

                @Override
                public void mouseClicked(MouseEvent e) {
                    if (SwingUtilities.isLeftMouseButton(e)) {
                        activeClass = file;
                        notifyObservers();
                    }
                }

                @Override
                public void mousePressed(MouseEvent e) {}

                @Override
                public void mouseReleased(MouseEvent e) {}

                @Override
                public void mouseEntered(MouseEvent e) {}

                @Override
                public void mouseExited(MouseEvent e) {}

            });
        }

    }

    private static class DirElements extends Elements {

        private boolean isVisible = true;

        public DirElements(File file, JPanel panel) {
            super(new ImageIcon("./system/icon/dir.png"), file.getName());
            addMouseListener(new MouseListener() {
                @Override
                public void mouseClicked(MouseEvent e) {
                    if(SwingUtilities.isLeftMouseButton(e)){
                        isVisible = !isVisible;
                        panel.setVisible(isVisible);
                    }
                }

                @Override
                public void mousePressed(MouseEvent e) {}

                @Override
                public void mouseReleased(MouseEvent e) {}

                @Override
                public void mouseEntered(MouseEvent e) {}

                @Override
                public void mouseExited(MouseEvent e) {}

            });
        }

    }

    private class CatalogProject {

        private final JPanel data;
        private final Map<String, CatalogProject> dirMap = new HashMap<>();

        public CatalogProject() {
            data = new JPanel();
            data.setLayout(new BoxLayout(data, BoxLayout.Y_AXIS));
        }

        public void add(String project, JavaClassDocument document) {
            String[] dir = document.getPaten().split("\\.");
            CatalogProject old = this;
            for (int i = 0; i < dir.length; i++) {
                project += "/" + dir[i];
                if (old.dirMap.containsKey(dir[i])) {
                     old = old.dirMap.get(dir[i]);
                } else if (i < dir.length -1) {
                    CatalogProject newCatalog = new CatalogProject();
                    DirElements butten = new DirElements(new File(project), newCatalog.data);
                    old.data.add(butten);
                    old.dirMap.put(dir[i], newCatalog);
                    JPanel indentPanel = new JPanel();
                    indentPanel.setLayout(new BoxLayout(indentPanel, BoxLayout.X_AXIS));
                    indentPanel.add(Box.createHorizontalStrut(25));
                    indentPanel.add(newCatalog.data);

                    old.data.add(indentPanel);
                    old = newCatalog;
                } else {
                    ClassElements butten = new ClassElements(document);
                    old.data.add(butten);
                }
            }
        }

    }

}
