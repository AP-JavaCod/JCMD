package edit;

import build.Builder;
import data.FileManager;
import edit.type.TypeJavaClass;

import javax.swing.text.AttributeSet;
import javax.swing.text.BadLocationException;
import javax.swing.text.DefaultStyledDocument;
import java.io.File;

public class JavaClassDocument extends DefaultStyledDocument {

    private File fileClass;
    private String name;
    private String paten;
    private String oldText;
    private boolean isMainClass;
    private TypeJavaClass typeJavaClass = null;

    public JavaClassDocument(File file) {
        fileClass = file;
        name = file.getName().split("\\.")[0];
        paten = Builder.getPathClass(file);
        oldText = FileManager.reader(file);
        isMainClass = setMainClass();
        try {
            super.insertString(0, oldText, null);
        } catch (BadLocationException e) {
            oldText = "";
        }
        for (TypeJavaClass c : TypeJavaClass.values()) {
            String type = c.NAME + " " + name;
            if (oldText.contains(type)) {
                typeJavaClass = c;
                break;
            }
        }
        if (typeJavaClass == null) {
            typeJavaClass = TypeJavaClass.CLASS;
        }
    }

    @Override
    public void insertString(int offs, String str, AttributeSet a) throws BadLocationException {
        String text = switch (str) {
            case "{" -> "{\n" + getTabs(getTabPosition(offs)) + "}";
            case "\n" -> "\n" + getTabs(getTabPosition(offs));
            case "(" -> "()";
            case "\"" -> "\"\"";
            case "\'" -> "\'\'";
            default -> str;
        };
        super.insertString(offs, text, a);
    }

    public File getFileClass() {
        return fileClass;
    }

    public String getName() {
        return name;
    }

    public String getPaten() {
        return paten;
    }

    public boolean isMainClass() {
        return isMainClass;
    }

    public TypeJavaClass getTypeJavaClass() {
        return typeJavaClass;
    }

    public boolean isChanges() {
        try {
            return !oldText.equals(getText(0, getLength()));
        } catch (BadLocationException e) {
            return false;
        }
    }

    public boolean save() {
        try {
            oldText = getText(0, getLength());
            FileManager.write(fileClass, oldText);
            return true;
        } catch (BadLocationException e) {
            return false;
        }
    }

    private boolean setMainClass() {
        return oldText.contains("public static void main(String[]");
    }

    private int getTabPosition(int end) {
        try {
            int tab = 0;
            String text = getText(0, end).substring(0, end);
            for (char el : text.toCharArray()) {
                if (el == '{') {
                    tab++;
                } else if (el == '}') {
                    tab--;
                }
            }
            return tab;
        } catch (BadLocationException e) {
            return 0;
        }
    }

    private String getTabs(int n) {
        return "\t".repeat(Math.max(0, n));
    }

}
