package decorator.ex1;

public class ComfortableSeat extends CondimentDecorator {
	Car car;
	
	public ComfortableSeat(Car car) {
		this.car = car;
	}
	
	public String getDescription() {
		return car.getDescription() + ", Comfortable Seat";
	}
	
	public int cost() {
		return car.cost() + 15;
	}
}
