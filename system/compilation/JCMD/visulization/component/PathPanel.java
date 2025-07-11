package visulization.component;

import build.Builder;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.io.*;
import java.util.*;
import java.util.List;

public class PathPanel extends JPanel{

    private final JTextArea cod;

    public PathPanel(JTextArea cod) {
        setLayout(new FlowLayout(FlowLayout.LEFT));
        this.cod = cod;
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

        public Elements(ImageIcon icon, String name){
            setLayout(new FlowLayout(FlowLayout.LEFT));
            BufferedImage bufferedImage = new BufferedImage(d, d,BufferedImage.TYPE_INT_ARGB);
            Graphics2D g2 = bufferedImage.createGraphics();
            g2.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BILINEAR);
            g2.drawImage(icon.getImage(), 0, 0, d, d, null);
            g2.dispose();

            add(new JLabel(new ImageIcon(bufferedImage)));
            add(new JLabel(name));
        }

    }

    private class ClassElements extends Elements {

        public ClassElements(File file) {
            super(new ImageIcon("./system/icon/java_class.png"), file.getName().split("\\.")[0]);
            addMouseListener(new MouseListener() {

                @Override
                public void mouseClicked(MouseEvent e) {
                    if (SwingUtilities.isLeftMouseButton(e)) {
                        try (FileReader reader = new FileReader(file)) {
                            int c;
                            StringBuilder code = new StringBuilder();
                            while ((c = reader.read()) != -1) {
                                code.append((char) c);
                            }
                            cod.setText(code.toString());
                        } catch (IOException ex) {
                            JOptionPane.showMessageDialog(null, "Not File");
                        }
                    }
                }

                @Override
                public void mousePressed(MouseEvent e) {

                }

                @Override
                public void mouseReleased(MouseEvent e) {

                }

                @Override
                public void mouseEntered(MouseEvent e) {

                }

                @Override
                public void mouseExited(MouseEvent e) {

                }
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
                public void mousePressed(MouseEvent e) {

                }

                @Override
                public void mouseReleased(MouseEvent e) {

                }

                @Override
                public void mouseEntered(MouseEvent e) {

                }

                @Override
                public void mouseExited(MouseEvent e) {

                }
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

        public void add(String project, List<String> dir) {
            project += "/" + dir.getFirst();
            if (dirMap.containsKey(dir.getFirst()) && dir.size() > 1) {
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
                ClassElements butten = new ClassElements(new File(project + ".java"));
                data.add(butten);
            }
        }

    }

}
