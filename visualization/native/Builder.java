import java.io.File;

public class Project {

    private long data =-1;

    public void open(File file){
        data = setData(file.getPath());
    }

    public void close(){
        deleteData(data);
        data = -1;
    }

    public String compilation(File mainClass, double version){
        error();
        return compilation(data, mainClass.getPath(), version);
    }

    public String build(File mainClass, double version){
        error();
        return build(data, mainClass.getPath(), version);
    }

    public String ran(File mainClass, double version){
       error();
       return ran(data, mainClass.getPath(), version);
    }

    private void error(){
        if(data == -1){
            throw new NullPointerException();
        }
    }

    private native long setData(String path);
    private native long deleteData(long data);
    private native String compilation(long data, String mainClass, double version);
    private native String build(long data, String mainClass, double version);
    private native  String ran(long data, String mainClass, double version);

    static {
        System.loadLibrary(".\\system\\compilation\\JICMD");
    }

}
