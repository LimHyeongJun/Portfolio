package decorator.ex1;

public class Navigation extends CondimentDecorator {
	Car car;
	
	public Navigation(Car car) {
		this.car = car;
	}
	
	public String getDescription() {
		return car.getDescription() + ", Navigation";
	}
	
	public int cost() {
		return car.cost() + 20;
	}
}
