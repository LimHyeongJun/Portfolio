package abstractFactory.ex2;

public class LuxuryCarStore extends CarStore {
	protected Car createCar() {
		Car car = null;
		CarFactory factory = new LuxuryCarFactory();
		
		car = new LuxuryCar(factory);
		
		return car;
	}
}
