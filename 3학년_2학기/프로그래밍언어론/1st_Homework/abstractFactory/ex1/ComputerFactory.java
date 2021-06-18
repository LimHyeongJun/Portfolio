package abstractFactory.ex1;

public interface ComputerFactory {
	public Keyboard createKeyboard();
	public Mouse createMouse();
	public Monitor createMonitor();
}
