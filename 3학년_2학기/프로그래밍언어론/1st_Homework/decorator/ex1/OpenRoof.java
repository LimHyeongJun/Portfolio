package decorator.ex1;

public class OpenRoof extends CondimentDecorator {
	Car car;
	
	public OpenRoof(Car car) {
		this.car = car;
	}
	
	public String getDescription() {
		return car.getDescription() + ", OpenRoof";
	}
	
	public int cost() {
		return car.cost() + 30;
	}
}
