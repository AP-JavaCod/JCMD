package build;

import edit.JavaClassDocument;

import java.io.File;
import java.io.IOException;

public class Builder {

    private static long data = -1;
    private static File projectFile = null;
    private static JavaClassDocument[] documents = null;

    public static void open(File file) throws IOException {
        if(isOpen()){
            throw new IOException();
        }
        data = setData(file.getPath());
        projectFile = new File(getProjectFile(data));
        int size = sizeClasses(data);
        documents = new JavaClassDocument[size];
        for (int i = 0; i < size; i++){
            documents[i] = new JavaClassDocument(new File(getClassFile(data, i)));
        }
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
        try {
            compilation(data, mainClass.getPath(), version);
            return "Not problem";
        } catch (JVMException e) {
            return e.getMessage();
        }
    }

    public static String build(File mainClass, String name, double version){
        error();
        try {
            compilation(data, mainClass.getPath(), version);
            build(data, mainClass.getPath(), name, version);
            return "Not problem";
        } catch (JVMException e) {
            return e.getMessage();
        }
    }

    public static String run(File mainClass, String name, double version){
       error();
       try {
           compilation(data, mainClass.getPath(), version);
           build(data, mainClass.getPath(), name, version);
           return run(data, mainClass.getPath(), name, version);
       } catch (JVMException e) {
           return e.getMessage();
       }
    }

    public static JavaClassDocument[] getDocument(){
        error();
        return documents;
    }

    public static String getPathClass(File file){
        error();
        return getPathClass(data, file.getPath());
    }

    public static File getProject(){
        return projectFile;
    }

    private static void error(){
        if(data == -1){
            throw new NullPointerException();
        }
    }

    public static native void console(String command);

    private static native long setData(String path);

    private static native int deleteData(long data);

    private static native void compilation(long data, String mainClass, double version) throws JVMException;

    private static native void build(long data, String mainClass, String name, double version);

    private static native  String run(long data, String mainClass, String name, double version);

    private static native int sizeClasses(long data);

    private static native String getClassFile(long data,int index);

    private static native String getPathClass(long data, String name);

    private static native String getProjectFile(long data);

    static {

        System.loadLibrary("./system/compilation/JICMD");

    }

}
