package decorator.ex1;

public class Truck extends Car {
	public Truck() {
		description = "Truck";
	}
	
	public int cost() {
		return 600;
	}
}
