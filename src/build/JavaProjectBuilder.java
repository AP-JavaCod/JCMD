package build;

import edit.JavaClassDocument;

import java.io.File;

public class JavaProjectBuilder {

    private long data;
    private File projectFile;
    private JavaClassDocument[] documents;

    public JavaProjectBuilder(File file) {
        data = setData(file.getPath());
        projectFile = new File(getProjectFile(data));
        int size = sizeClasses(data);
        documents = new JavaClassDocument[size];
        for (int i = 0; i < size; i++){
            File doc = new File(getClassFile(data, i));
            documents[i] = new JavaClassDocument(doc, getPathClass(doc));
        }
    }

    public void close(){
        deleteData(data);
        data = -1;
    }

    public void compilation(File buildDir, File mainClass, double version) throws JVMException{
        error();
        compilation(data, buildDir.getPath(), mainClass.getPath(), version);
    }

    public void build(File buildDir, File mainClass, String nameJarFile, double version) throws JVMException{
        error();
        compilation(buildDir, mainClass, version);
        build(data, buildDir.getPath(), mainClass.getPath(), nameJarFile, version);
    }

    public String run(File buildDir, File mainClass, String nameJavaFile, double version) throws JVMException{
        error();
        build(buildDir, mainClass, nameJavaFile, version);
        return run(data, buildDir.getPath(), mainClass.getPath(), nameJavaFile, version);
    }

    public JavaClassDocument[] getDocument(){
        error();
        return documents;
    }

    public String getPathClass(File file){
        error();
        return getPathClass(data, file.getPath());
    }

    public File getProject(){
        return projectFile;
    }

    private void error(){
        if(data == -1){
            throw new NullPointerException();
        }
    }

    public final native void console(String command);

    private native long setData(String path);

    private native int deleteData(long data);

    private native void compilation(long data, String buildDir,  String mainClass, double version) throws JVMException;

    private native void build(long data, String buildDir, String mainClass, String nameJarFile, double version);

    private native String run(long data, String buildDir, String mainClass, String nameJarFile, double version);

    private native int sizeClasses(long data);

    private native String getClassFile(long data,int index);

    private native String getPathClass(long data, String name);

    private native String getProjectFile(long data);

    static {

        System.loadLibrary("./system/compilation/JICMD");

    }


}
