package abstractFactory.ex1;

public class LGComputerFactory implements ComputerFactory {
	public Keyboard createKeyboard() {
		return new LGKeyboard();
	}

	public Mouse createMouse() {
		return new LGMouse();
	}

	public Monitor createMonitor() {
		return new LGMonitor();
	}
}
