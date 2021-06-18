package decorator.ex2;

public class Main {
	public static void main(String[] args) {
		System.out.println("--------Decorator pattern example 2--------");
		
		Hamburger shrimpBurger = new BasicBread();
		shrimpBurger = new ShrimpPatty(shrimpBurger);
		shrimpBurger = new Lettuce(shrimpBurger);
		shrimpBurger = new Tomato(shrimpBurger);
		System.out.println("Shrimp Burger = " + shrimpBurger.getDescription());
		
		Hamburger cheeseBulgogiBurger = new RyeBread();
		cheeseBulgogiBurger = new Cheese(cheeseBulgogiBurger);
		cheeseBulgogiBurger = new BulgogiPatty(cheeseBulgogiBurger);
		cheeseBulgogiBurger = new Lettuce(cheeseBulgogiBurger);
		cheeseBulgogiBurger = new Tomato(cheeseBulgogiBurger);
		System.out.println("Cheese Bulgogi Burger = " + cheeseBulgogiBurger.getDescription());
	}
}
