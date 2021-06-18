package abstractFactory.ex1;

public class LGComputer extends Computer {
	ComputerFactory factory;
	
	public LGComputer(ComputerFactory factory) {
		this.factory = factory;
	}
	
	void assemble() {
		name = "LG Computer";
		System.out.println("Make " + name);
		keyboard = factory.createKeyboard();
		monitor = factory.createMonitor();
		mouse = factory.createMouse();
	}
}
