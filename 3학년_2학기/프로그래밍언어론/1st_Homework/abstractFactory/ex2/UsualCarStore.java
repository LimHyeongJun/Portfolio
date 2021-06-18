package abstractFactory.ex2;

public class UsualCarStore extends CarStore{
	protected Car createCar() {
		Car car = null;
		CarFactory factory = new UsualCarFactory();
		
		car = new UsualCar(factory);
		
		return car;
	}
}
