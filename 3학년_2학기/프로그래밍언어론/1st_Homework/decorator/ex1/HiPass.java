package decorator.ex1;

public class HiPass extends CondimentDecorator {
	Car car;
	
	public HiPass(Car car) {
		this.car = car;
	}
	
	public String getDescription() {
		return car.getDescription() + ", hiPass";
	}
	
	public int cost() {
		return car.cost() + 13;
	}
}
