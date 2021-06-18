package observer.ex3;

public class NewsPaperSubscriber implements Observer {
	private String name;
	private String title;
	private String news;
	private NewsPaperPublisher newsPaperPublisher;
	
	public NewsPaperSubscriber(String name, NewsPaperPublisher newsPaperPublisher) {
		this.name = name;
		this.newsPaperPublisher = newsPaperPublisher;
		newsPaperPublisher.registerObserver(this);
	}
	
	public void update(String title, String news) {
		this.title = title;
		this.news = news;
		display();
	}
	
	public void display() {
		System.out.println("---" + name + " watches " + title + "---");
		System.out.println(news);
	}
}
