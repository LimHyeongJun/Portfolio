package strategy.ex1;

public class SportsCar extends Car {
	public SportsCar(CarMoveBehavior carMoveBehavior) {
		super(carMoveBehavior);
	}

	public void display() {
		System.out.println("This is Sports Car");
	}
}
