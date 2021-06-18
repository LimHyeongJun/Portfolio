package abstractFactory.ex2;

public class OffRoadCarStore extends CarStore {
	protected Car createCar() {
		Car car = null;
		CarFactory factory = new OffRoadCarFactory();
		
		car = new OffRoadCar(factory);
		
		return car;
	}
}
