package observer.ex3;

public class Main {
	public static void main(String[] args) {
		System.out.println("--------Observer pattern example 3--------");
		NewsPaperPublisher kw = new NewsPaperPublisher();
		
		NewsPaperSubscriber s1 = new NewsPaperSubscriber("Juliet", kw);
		NewsPaperSubscriber s2 = new NewsPaperSubscriber("Romeo", kw);
		NewsPaperSubscriber s3 = new NewsPaperSubscriber("Zeus", kw);
		
		kw.setNews("Big News!", "The end of the US presidential election is imminent");
		
		kw.removeObserver(s1);
		System.out.println("\n-----After remove 1 observer-----");
		
		kw.setNews("Weather Forecast", "Tomorrow will be colder than today. It will rain nationwide, so please bring an umbrella.");
	}
}
