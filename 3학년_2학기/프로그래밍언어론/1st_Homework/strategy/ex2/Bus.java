package strategy.ex2;

public class Bus extends PublicTransport {
	public Bus() {
		setMovable(new LoadMovable());
	}
	
	public void display() {
		System.out.println("This is Bus");
	}
}
