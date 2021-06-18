package abstractFactory.ex2;

public class OffRoadCarFactory implements CarFactory {
	public Wheel createWheel() {
		return new BigWheel();
	}

	public Seat createSeat() {
		return new ComfortableSeat();
	}

	public Navigation createNavigation() {
		return new NarrowNavigation();
	}
}
