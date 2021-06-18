package template.ex1;

public abstract class Potion {
	final void prepareRecipe() {
		prepareExactAmount();
		pourInBottle();
		addFlavors();
	}
	
	abstract void prepareExactAmount();
	
	abstract void addFlavors();
	
	void pourInBottle() {
		System.out.println("Pouring into Bottle");
	}
}
