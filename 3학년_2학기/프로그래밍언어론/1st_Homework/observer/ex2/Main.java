package observer.ex2;

public class Main {
	public static void main(String[] args) {
		System.out.println("--------Observer pattern example 2--------");
		
		Singer twice = new Singer();
		
		SingerFan fan1 = new SingerFan("John", twice);
		SingerFan fan2 = new SingerFan("Judy", twice);
		SingerFan fan3 = new SingerFan("Harry", twice);
		SingerFan fan4 = new SingerFan("Potter", twice);
		
		twice.speak("사랑합니다");
		System.out.println();
		twice.speak("감사합니다");
	}
}
