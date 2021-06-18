package decorator.ex1;

public class Main {
	public static void main(String[] args) {
		System.out.println("--------Decorator pattern example 1--------");
		
		Car car1 = new Truck();
		car1 = new HiPass(car1);
		car1 = new Navigation(car1);
		System.out.println(car1.getDescription() + " $" + car1.cost());
		
		
		Car car2 = new OpenCar();
		car2 = new OpenRoof(car2);
		car2 = new AirBag(car2);
		car2 = new ComfortableSeat(car2);
		System.out.println(car2.getDescription() + " $" + car2.cost());
		
		Car car3 = new SportsCar();
		car3 = new AirBag(car3);
		car3 = new GoodWheel(car3);
		car3 = new ComfortableSeat(car3);
		System.out.println(car3.getDescription() + " $" + car3.cost());
	}
}
