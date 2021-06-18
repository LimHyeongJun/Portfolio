package abstractFactory.ex1;

public class SamsungComputerFactory implements ComputerFactory {
	public Keyboard createKeyboard() {
		return new SamsungKeyboard();
	}

	public Mouse createMouse() {
		return new SamsungMouse();
	}
	
	public Monitor createMonitor() {
		return new SamsungMonitor();
	}
}
