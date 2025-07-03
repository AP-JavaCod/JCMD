import java.io.File;

public class Builder {

    private static long data =-1;

    public static void open(File file){
        data = setData(file.getPath());
    }

    public static void close(){
        deleteData(data);
        data = -1;
    }

    public static String compilation(File mainClass, double version){
        error();
        return compilation(data, mainClass.getPath(), version);
    }

    public static String build(File mainClass, String name, double version){
        error();
        return build(data, mainClass.getPath(), name, version);
    }

    public static String ran(File mainClass, String name, double version){
       error();
       return ran(data, mainClass.getPath(), name, version);
    }

    private static void error(){
        if(data == -1){
            throw new NullPointerException();
        }
    }

    private static native long setData(String path);
    private static native int deleteData(long data);
    private static native String compilation(long data, String mainClass, double version);
    private static native String build(long data, String mainClass, String name, double version);
    private static native  String ran(long data, String mainClass, String name, double version);

    static {
        System.loadLibrary("system/compilation/JICMD");
    }

}
