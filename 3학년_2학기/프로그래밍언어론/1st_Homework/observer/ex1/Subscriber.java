package observer.ex1;

public class Subscriber implements Observer{
	private String name;
	private String title;
	private Youtube youtube;
	
	public Subscriber(String name, Youtube youtube) {
		this.name = name;
		this.youtube = youtube;
		youtube.registerObserver(this);
	}
	
	public void update(String title) {
		this.title = title;
		display();
	}
	
	public void display() {
		System.out.println(name + " watches " + title);
	}
}
