package decorator.ex2;

public abstract class Ingredient extends Hamburger{
	Hamburger hamburger;
	
	public Ingredient(Hamburger hamburger) {
		this.hamburger = hamburger;
	}
}
