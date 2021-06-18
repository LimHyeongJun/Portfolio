package decorator.ex1;

public class AirBag extends CondimentDecorator {
	Car car;
	
	public AirBag(Car car) {
		this.car = car;
	}
	
	public String getDescription() {
		return car.getDescription() + ", AirBag";
	}
	
	public int cost() {
		return car.cost() + 30;
	}
}
