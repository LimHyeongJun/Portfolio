package decorator.ex2;

public class ShrimpPatty extends Ingredient {
	public ShrimpPatty(Hamburger hamburger) {
		super(hamburger);
	}

	public String getDescription() {
		return hamburger.getDescription() + ", shrimp patty";
	}
}
