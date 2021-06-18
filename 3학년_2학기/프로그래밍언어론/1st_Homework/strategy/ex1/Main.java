package strategy.ex1;

public class Main {
	public static void main(String[] args) {
		System.out.println("--------Strategy pattern example 1--------");
		
		Car car1 = new SportsCar(new UpBehavior());
		car1.display();
		car1.move();
		
		Car car2 = new GeneralCar(new DownBehavior());
		car2.display();
		car2.move();
		
		car2.setMoveBehavior(new LeftBehavior());
		car2.move();
		
		car2.setMoveBehavior(new RightBehavior());
		car2.move();
	}
}
