package abstractFactory.ex2;

public class UsualCar extends Car {
	CarFactory carFactory;
	
	public UsualCar(CarFactory carFactory) {
		this.carFactory = carFactory;
	}
	protected void prepare() {
		name = "Usual Car";
		System.out.println("Assemble " + name);
		wheel = carFactory.createWheel();
		navigation = carFactory.createNavigation();
		seat = carFactory.createSeat();
	}
}
