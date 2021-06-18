package decorator.ex3;

public class ChocolateCake extends Cake {
	public ChocolateCake() {
		description = "Chocolate Cake";
	}
	
	public int cost() {
		return 150;
	}
}
