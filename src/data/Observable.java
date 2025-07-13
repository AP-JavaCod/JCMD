package data;

public interface Observable {

    void addObserver(Observer observer);

    void notifyObservers();

    void removeObserver(Observer observer);

}
