package abstractFactory.ex2;

public class LuxuryCar extends Car {
	CarFactory carFactory;
	
	public LuxuryCar(CarFactory carFactory) {
		this.carFactory = carFactory;
	}
	protected void prepare() {
		name = "Luxury Car";
		System.out.println("Assemble " + name);
		wheel = carFactory.createWheel();
		navigation = carFactory.createNavigation();
		seat = carFactory.createSeat();
	}
}
