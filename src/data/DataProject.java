package data;

import edit.JavaClassDocument;
import java.util.*;

public class DataProject implements Observable{

    private JavaClassDocument activeClass = null;
    private boolean isMainClass = false;
    private final List<Observer> observers = new ArrayList<>();

    public void setActiveClass(JavaClassDocument file){
        activeClass = file;
        isMainClass = file.isMainClass();
        notifyObservers();
    }

    public JavaClassDocument getActiveClass(){
        return activeClass;
    }

    @Override
    public void addObserver(Observer observer) {
        observers.add(observer);
    }

    @Override
    public void notifyObservers() {
        for (Observer i : observers) {
            i.upData();
        }
    }

    @Override
    public void removeObserver(Observer observer){
        observers.remove(observer);
    }

}
