package strategy.ex2;

public class Main {
	public static void main(String[] args) {
		PublicTransport bus = new Bus();
		PublicTransport train = new Train();
		
		System.out.println("--------Strategy pattern example 2--------");
		
		bus.display();
		bus.performMove();
		
		System.out.println();
		
		train.display();
		train.performMove();
	}
}
