package abstractFactory.ex1;

public class LGComputerStore extends ComputerStore {
	protected Computer createComputer() {
		Computer computer = null;
		ComputerFactory factory = new LGComputerFactory();
		
		computer = new LGComputer(factory);
		
		return computer;
	}
}
