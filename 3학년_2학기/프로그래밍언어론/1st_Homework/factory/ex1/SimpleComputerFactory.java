package factory.ex1;

public class SimpleComputerFactory {
	Computer computer;
	
	public SimpleComputerFactory() {
		computer = null;
	}
	
	public Computer getComputer(String type) {		
		if(type.equals("desktop")) {
			computer =  new Desktop();
		} else if(type.equals("laptop")) {
			computer = new Laptop();
		} else if(type.equals("tablet")) {
			computer = new Tablet();
		} else {
			computer = new NoComputer();
		}
		
		return computer;
	}
}
