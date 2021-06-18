package strategy.ex1;

public class GeneralCar extends Car {
	public GeneralCar(CarMoveBehavior carMoveBehavior) {
		super(carMoveBehavior);
	}

	public void display() {
		System.out.println("This is general car");
	}
}
