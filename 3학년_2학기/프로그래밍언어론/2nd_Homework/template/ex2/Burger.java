package template.ex2;

public abstract class Burger {
	final void prepareRecipe() {
		stackUpBread();
		stackUpPatty();
		stackUpIngredient();
		stackUpBread();
	}
	
	public void stackUpBread() {
		System.out.println("Stack up bread");
	}
	
	abstract void stackUpPatty();
	
	abstract void stackUpIngredient(); 
}
