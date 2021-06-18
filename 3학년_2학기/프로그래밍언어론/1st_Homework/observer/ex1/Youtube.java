package observer.ex1;

import java.util.*;

public class Youtube implements Subject {
	private ArrayList observers;
	private String title;
	
	public Youtube() {
		observers = new ArrayList();
	}
	
	public void registerObserver(Observer o) {
		observers.add(o);
	}
	
	public void removeObserver(Observer o) {
		int i = observers.indexOf(o);
		if(i >= 0)
			observers.remove(i);
	}
	
	public void notifyObservers() {
		for(int i = 0; i < observers.size(); i++) {
			Observer observer = (Observer)observers.get(i);
			observer.update(title);
		}
	}
	
	public void newVideoUpdate() {
		notifyObservers();
	}
	
	public void setTitle(String title) {
		this.title = title;
		newVideoUpdate();
	}
	
	public String getTitle() {
		return title;
	}
}
