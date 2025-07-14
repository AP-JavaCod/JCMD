package data;

import edit.JavaClassDocument;
import java.util.*;

public class DataProject implements Observable{

    private JavaClassDocument activeClass = null;
    private final List<Observer> observers = new ArrayList<>();

    public void setActiveClass(JavaClassDocument file){
        activeClass = file;
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
