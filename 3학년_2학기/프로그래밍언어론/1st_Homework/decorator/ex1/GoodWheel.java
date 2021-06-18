package decorator.ex1;

public class GoodWheel extends CondimentDecorator {
	Car car;
	
	public GoodWheel(Car car) {
		this.car = car;
	}
	
	public String getDescription() {
		return car.getDescription() + ", Good Wheel";
	}
	
	public int cost() {
		return car.cost() + 10;
	}
}
