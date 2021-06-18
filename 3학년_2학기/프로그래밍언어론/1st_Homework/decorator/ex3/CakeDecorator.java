package decorator.ex3;

public abstract class CakeDecorator extends Cake {
	Cake cake;
	
	public CakeDecorator(Cake cake) {
		this.cake = cake;
	}

	public abstract String getDescription();
}
