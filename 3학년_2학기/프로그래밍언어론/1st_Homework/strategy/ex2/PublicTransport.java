package strategy.ex2;

public abstract class PublicTransport {
	private Movable movable;
	
	public abstract void display();
	
	public PublicTransport() { }
	
	public void setMovable(Movable movable) {
		this.movable = movable;
	}
	
	public Movable getMovable() {
		return this.movable;
	}
	
	public void performMove() {
		movable.move();
	}
}
