package abstractFactory.ex3;

public interface PotionFactory {
	public Taste createTaste();
	public Bottle createBottle();
	public Amount createAmount();
}
