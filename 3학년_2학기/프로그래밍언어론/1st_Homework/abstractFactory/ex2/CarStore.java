package abstractFactory.ex2;

public abstract class CarStore {
	protected abstract Car createCar();
	
	public Car orderCar() {
		Car car = createCar();
		
		car.prepare();
		
		return car;
	}
}
