package decorator.ex1;

public class SportsCar extends Car {
	public SportsCar() {
		description = "SportsCar";
	}
	
	public int cost() {
		return 700;
	}
}
