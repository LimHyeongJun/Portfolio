package decorator.ex2;

public class Tomato extends Ingredient {
	public Tomato(Hamburger hamburger) {
		super(hamburger);
	}

	public String getDescription() {
		return hamburger.getDescription() + ", tomato";
	}

}
