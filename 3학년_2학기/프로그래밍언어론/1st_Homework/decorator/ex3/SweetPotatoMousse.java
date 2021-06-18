package decorator.ex3;

public class SweetPotatoMousse extends CakeDecorator {
	public SweetPotatoMousse(Cake cake) {
		super(cake);
	}
	
	public String getDescription() {
		return cake.getDescription() + "Sweet Potato Mousse";
	}
	
	public int cost() {
		return cake.cost() + 25;
	}
}
