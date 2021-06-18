package abstractFactory.ex2;

public class UsualCarFactory implements CarFactory  {
	public Wheel createWheel() {
		return new UsualWheel();
	}

	public Seat createSeat() {
		return new UsualSeat();
	}

	public Navigation createNavigation() {
		return new UsualNavigation();
	}
}
