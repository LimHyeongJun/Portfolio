package abstractFactory.ex2;

public class OffRoadCar extends Car {
	CarFactory carFactory;
	
	public OffRoadCar(CarFactory carFactory) {
		this.carFactory = carFactory;
	}
	protected void prepare() {
		name = "Off Road Car";
		System.out.println("Assemble " + name);
		wheel = carFactory.createWheel();
		navigation = carFactory.createNavigation();
		seat = carFactory.createSeat();
	}
}
