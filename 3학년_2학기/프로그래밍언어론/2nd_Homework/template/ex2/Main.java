package template.ex2;

public class Main {
	public static void main(String[] args) {
		BulgogiBurger bulgogiBurger = new BulgogiBurger();
		ShrimpBurger shrimpBurger = new ShrimpBurger();
		CheeseBurger cheeseBurger = new CheeseBurger();
		
		System.out.println("\nMaking Bulgogi Burger...");
		bulgogiBurger.prepareRecipe();
		
		System.out.println("\nMaking Shrimp Burger...");
		shrimpBurger.prepareRecipe();
		
		System.out.println("\nMaking Cheese Burger...");
		cheeseBurger.prepareRecipe();
	}
}
