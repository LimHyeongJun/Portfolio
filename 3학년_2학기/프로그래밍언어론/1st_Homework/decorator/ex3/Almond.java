package decorator.ex3;

public class Almond extends CakeDecorator {
	public Almond(Cake cake) {
		super(cake);
	}
	
	public String getDescription() {
		return cake.getDescription() + ", Almond";
	}
	
	public int cost() {
		return cake.cost() + 10;
	}
}
