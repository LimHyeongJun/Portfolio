package abstractFactory.ex1;

public class Main {
	public static void main(String[] args) {
		System.out.println("--------Abstract factory pattern example 1--------");
		
		ComputerStore samsungStore = new SamsungComputerStore();
		ComputerStore lgStore = new LGComputerStore();
		
		Computer computer = samsungStore.orderComputer();
		System.out.println(computer + "\n");
		
		computer = lgStore.orderComputer();
		System.out.println(computer + "\n");
	}
}
