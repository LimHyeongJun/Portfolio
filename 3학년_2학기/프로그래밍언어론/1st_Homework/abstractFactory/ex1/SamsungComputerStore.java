package abstractFactory.ex1;

public class SamsungComputerStore extends ComputerStore {
	protected Computer createComputer() {
		Computer computer = null;
		
		ComputerFactory computerFactory = new SamsungComputerFactory();
		
		computer = new SamsungComputer(computerFactory);
		
		return computer;
	}
}
