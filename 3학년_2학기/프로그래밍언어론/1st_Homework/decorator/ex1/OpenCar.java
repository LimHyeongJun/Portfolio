package decorator.ex1;

public class OpenCar extends Car {
	public OpenCar() {
		description = "OpenCar";
	}
	
	public int cost() {
		return 500;
	}
}
