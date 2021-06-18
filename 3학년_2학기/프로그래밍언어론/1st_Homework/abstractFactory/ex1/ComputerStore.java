package abstractFactory.ex1;

public abstract class ComputerStore {
	protected abstract Computer createComputer();
	
	public Computer orderComputer() {
		Computer computer = createComputer();
		
		computer.assemble();
		
		return computer;
	}
}
