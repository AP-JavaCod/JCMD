package data;

import javax.swing.*;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class FileManager {

    public static String reader(File file){
        try (FileReader reader = new FileReader(file)) {
            int c;
            StringBuilder code = new StringBuilder();
            while ((c = reader.read()) != -1) {
                code.append((char) c);
            }
            return code.toString();
        } catch (IOException e) {
            JOptionPane.showMessageDialog(null, "Not File");
        }
        return null;
    }

    public static void write(File file, String text){
        try(FileWriter writer = new FileWriter(file)) {
            writer.write(text);
            writer.flush();
        }catch (IOException e){
            JOptionPane.showMessageDialog(null, "Not save file");
        }
    }


}
