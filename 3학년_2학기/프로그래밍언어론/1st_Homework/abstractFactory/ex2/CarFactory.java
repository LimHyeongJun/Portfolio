package abstractFactory.ex2;

public interface CarFactory {
	public Wheel createWheel();
	public Seat createSeat();
	public Navigation createNavigation();
}
