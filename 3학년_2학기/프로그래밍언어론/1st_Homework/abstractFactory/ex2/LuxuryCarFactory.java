package abstractFactory.ex2;

public class LuxuryCarFactory implements CarFactory{
	public Wheel createWheel() {
		return new NiceWheel();
	}

	public Seat createSeat() {
		return new ComfortableSeat();
	}

	public Navigation createNavigation() {
		return new WideNavigation();
	}
}
