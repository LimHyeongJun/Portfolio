package factory.ex1;

public class ComputerStore {
	SimpleComputerFactory factory;
	
	public ComputerStore(SimpleComputerFactory factory) {
		this.factory = factory;
	}
	
	public Computer orderComputer(String type) {
		Computer computer = null;
		
		computer = factory.getComputer(type);
		
		return computer;
	}
}
