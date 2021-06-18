package strategy.ex2;

public class Train extends PublicTransport {
	public Train() {
		setMovable(new RailLoadMovable());
	}
	
	public void display() {
		System.out.println("This is Train");
	}
}
