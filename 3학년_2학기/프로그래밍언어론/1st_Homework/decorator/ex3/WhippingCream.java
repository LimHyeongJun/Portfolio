package decorator.ex3;

public class WhippingCream extends CakeDecorator{
	public WhippingCream(Cake cake) {
		super(cake);
	}
	
	public String getDescription() {
		return cake.getDescription() + ", Whipping Cream";
	}
	
	public int cost() {
		return cake.cost() + 15;
	}
}
