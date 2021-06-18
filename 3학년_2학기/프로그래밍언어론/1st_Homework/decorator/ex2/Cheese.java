package decorator.ex2;

public class Cheese extends Ingredient {
	public Cheese(Hamburger hamburger) {
		super(hamburger);
	}

	public String getDescription() {
		return hamburger.getDescription() + ", cheese";
	}
}
