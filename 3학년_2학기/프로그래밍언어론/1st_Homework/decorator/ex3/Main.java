package decorator.ex3;

public class Main {
	public static void main(String[] args) {
		System.out.println("--------Decorator pattern example 3--------");
		
		Cake strawberryCake = new StrawberryCake();
		Cake chocolateCake = new ChocolateCake();
		System.out.println(strawberryCake.getDescription() + " $" + strawberryCake.cost());
		System.out.println(chocolateCake.getDescription() + " $" + chocolateCake.cost());
		
		System.out.println("\n" + "¡ÚAfter Decorating¡Ú");
		
		strawberryCake = new WhippingCream(strawberryCake);
		strawberryCake = new Almond(strawberryCake);
		System.out.println(strawberryCake.getDescription() + " $" + strawberryCake.cost());
		
		chocolateCake = new WhippingCream(chocolateCake);
		chocolateCake = new SweetPotatoMousse(chocolateCake);
		System.out.println(chocolateCake.getDescription() + " $" + chocolateCake.cost());
	}
}
