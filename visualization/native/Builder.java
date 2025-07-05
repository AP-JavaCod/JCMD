import java.io.File;
import java.io.IOException;

public class Builder {

    private static long data =-1;

    public static void open(File file) throws IOException {
        if(isOpen()){
            throw new IOException();
        }
        data = setData(file.getPath());
    }

    public static boolean isOpen(){
        return data != -1;
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

    public static String run(File mainClass, String name, double version){
       error();
       return run(data, mainClass.getPath(), name, version);
    }

    public static File[] getClasses(){
        error();
        int size = sizeClasses(data);
        File[] classes = new File[size];
        for (int i = 0; i < size; i++){
            classes[i] = new File(getClassFile(data, i));
        }
        return classes;
    }

    public static String[] getClassesFormat(){
        error();
        int size = sizeClasses(data);
        String[] classes = new String[size];
        for (int i = 0; i < size; i++){
            classes[i] = getClassFormat(data, i);
        }
        return classes;
    }

    public static File getProject(){
        return new File(getProjectFile(data));
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

    private static native  String run(long data, String mainClass, String name, double version);

    private static native int sizeClasses(long data);

    private static native String getClassFile(long data,int index);

    private static native String getClassFormat(long data, int index);

    private static native String getProjectFile(long data);

    static {
        System.loadLibrary("system/compilation/JICMD");
    }

}
