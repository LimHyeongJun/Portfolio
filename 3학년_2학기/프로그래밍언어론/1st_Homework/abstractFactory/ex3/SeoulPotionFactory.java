package abstractFactory.ex3;

public class SeoulPotionFactory implements PotionFactory {
	String type;
	int level;
	
	public SeoulPotionFactory(String type, int level) {
		this.type = type;
		this.level = level;
	}
	
	public Taste createTaste() {
		if(type.equalsIgnoreCase("hp"))
			return new StrawberryTaste(level);
		else if(type.equalsIgnoreCase("mp"))
			return new GrapeTaste(level);
		
		return null;
	}

	public Bottle createBottle() {
		return new SeoulStyleBottle(level);
	}

	public Amount createAmount() {
		return new SeoulAmount(level);
	}
}
