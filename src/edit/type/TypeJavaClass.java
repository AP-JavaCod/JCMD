package edit.type;

import java.awt.*;

public enum TypeJavaClass {

    CLASS("class", new Color(0, 0, 128)),
    INTERFACE("interface", new Color(0, 128, 0)),
    ENUM("enum", new Color(128, 0, 128));

    public final String NAME;
    public final Color COLOR;

    TypeJavaClass(String name, Color color){
        NAME = name;
        COLOR = color;
    }

}
