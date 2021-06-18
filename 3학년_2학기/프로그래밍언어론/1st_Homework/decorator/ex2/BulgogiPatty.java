package decorator.ex2;

public class BulgogiPatty extends Ingredient {
	public BulgogiPatty(Hamburger hamburger) {
		super(hamburger);
	}
	
	public String getDescription() {
		return hamburger.getDescription() + ", bulgogi patty";
	}
}
