package observer.ex3;

import java.util.ArrayList;

public class NewsPaperPublisher implements Subject {
	private ArrayList observers;
	private String title;
	private String news;
	
	public NewsPaperPublisher() {
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
			observer.update(title, news);
		}
	}
	
	public void newVideoUpdate() {
		notifyObservers();
	}
	
	public void setNews(String title, String news) {
		this.title = title;
		this.news = news;
		newVideoUpdate();
	}
}
