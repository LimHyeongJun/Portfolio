package observer.ex1;

public class Main {
	public static void main(String[] args) {
		System.out.println("--------Observer pattern example 1--------");
		
		Youtube hyeongJunYoutube = new Youtube();
		
		Subscriber s1 = new Subscriber("John", hyeongJunYoutube);
		Subscriber s2 = new Subscriber("Tom", hyeongJunYoutube);
		Subscriber s3 = new Subscriber("Alice", hyeongJunYoutube);
		Subscriber s4 = new Subscriber("Trump", hyeongJunYoutube);
		
		hyeongJunYoutube.setTitle("BTS MV reaction");
		
		hyeongJunYoutube.removeObserver(s1);
		System.out.println("\n-----After remove 1 observer-----");
		
		hyeongJunYoutube.setTitle("Chicken Mukbang");
	}
}
