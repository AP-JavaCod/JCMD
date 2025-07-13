package visulization.component;

import build.Builder;
import edit.JavaClassDocument;
import visulization.MenuFrame;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.io.*;
import java.util.*;
import java.util.List;

public class PathPanel extends JPanel{


    public PathPanel() {
        setLayout(new FlowLayout(FlowLayout.LEFT));
        String[] f = Builder.getClassesFormat();
        CatalogProject catalog = new CatalogProject();
        String project = Builder.getProject().getPath() + "/src";
        for (String s : f) {
            List<String> data = new ArrayList<>(Arrays.asList(s.split("\\.")));
            catalog.add(project, data);
        }
        add(catalog.data);
    }

    private static class Elements extends JPanel{

        private static final int d = 25;
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
            add(ICON);
            add(NAME);
        }

    }

    private static class ClassElements extends Elements {

        private static final ImageIcon MAIN_CLASS = new ImageIcon("./system/icon/main_class.png");
        private static final ImageIcon JAVA_CLASS = new ImageIcon("./system/icon/java_class.png");

        public ClassElements(JavaClassDocument file) {
            super(file.isMainClass() ? MAIN_CLASS : JAVA_CLASS, file.getName());
            NAME.setForeground(file.getTypeJavaClass().COLOR);
            addMouseListener(new MouseListener() {

                @Override
                public void mouseClicked(MouseEvent e) {
                    if (SwingUtilities.isLeftMouseButton(e)) {
                        MenuFrame.project.setActiveClass(file);
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

    private static class CatalogProject {

        private final JPanel data;
        private final Map<String, CatalogProject> dirMap = new HashMap<>();

        public CatalogProject() {
            data = new JPanel();
            data.setLayout(new BoxLayout(data, BoxLayout.Y_AXIS));
        }

        public void add(String project, List<String> dir) {
            project += "/" + dir.getFirst();
            if (dirMap.containsKey(dir.getFirst())) {
                dirMap.get(dir.removeFirst()).add(project, dir);
            } else if (dir.size() > 1) {
                CatalogProject newCatalog = new CatalogProject();
                DirElements butten = new DirElements(new File(project),newCatalog.data);
                data.add(butten);
                dirMap.put(dir.removeFirst(), newCatalog);
                JPanel indentPanel = new JPanel();
                indentPanel.setLayout(new BoxLayout(indentPanel, BoxLayout.X_AXIS));
                indentPanel.add(Box.createHorizontalStrut(10));
                indentPanel.add(newCatalog.data);

                data.add(indentPanel);
                newCatalog.add(project, dir);
            } else {
                ClassElements butten = new ClassElements(new JavaClassDocument(new  File(project + ".java")));
                data.add(butten);
            }
        }

    }

}
