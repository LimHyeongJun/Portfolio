package abstractFactory.ex2;

public class Main {
	public static void main(String[] args) {
		System.out.println("--------Abstract factory pattern example 2--------");
		
		CarStore offRoadCarStore = new OffRoadCarStore();
		CarStore luxuryCarStore = new LuxuryCarStore();
		CarStore usualCarStore = new UsualCarStore();
		
		Car offRoadCar = offRoadCarStore.orderCar();
		System.out.println(offRoadCar + "\n");
		
		Car luxuryCar = luxuryCarStore.orderCar();
		System.out.println(luxuryCar + "\n");
		
		Car usualCar = usualCarStore.orderCar();
		System.out.println(usualCar + "\n");
	}
}
