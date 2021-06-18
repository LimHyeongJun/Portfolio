package decorator.ex2;

public class Lettuce extends Ingredient {
	public Lettuce(Hamburger hamburger) {
		super(hamburger);
	}
	
	public String getDescription() {
		return hamburger.getDescription() + ", lettuce";
	}
}
