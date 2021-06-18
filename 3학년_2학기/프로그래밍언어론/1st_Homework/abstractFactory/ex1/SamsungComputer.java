package abstractFactory.ex1;

public class SamsungComputer extends Computer {
	ComputerFactory factory;
	
	public SamsungComputer(ComputerFactory factory) {
		this.factory = factory;
	}
	
	void assemble() {
		name = "Samsung Computer";
		System.out.println("Make " + name);
		keyboard = factory.createKeyboard();
		monitor = factory.createMonitor();
		mouse = factory.createMouse();
	}
}
