package abstractFactory.ex3;

public class BusanPotionFactory implements PotionFactory {
	String type;
	int level;
	
	public BusanPotionFactory(String type, int level) {
		this.type = type;
		this.level = level;
	}
	
	public Taste createTaste() {
		if(type.equalsIgnoreCase("hp"))
			return new AppleTaste(level);
		else if(type.equalsIgnoreCase("mp"))
			return new MelonTaste(level);
		
		return null;
	}

	public Bottle createBottle() {
		return new BusanStyleBottle(level);
	}

	public Amount createAmount() {
		return new BusanAmount(level);
	}

}
