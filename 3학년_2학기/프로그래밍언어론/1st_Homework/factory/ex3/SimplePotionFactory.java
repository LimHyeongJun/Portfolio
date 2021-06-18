package factory.ex3;


public class SimplePotionFactory {
	Potion potion;
	
	public SimplePotionFactory() {
		potion = null;
	}
	public Potion createPotion(String type) {
		if (type.equalsIgnoreCase("hp")) {
			potion = new HpPotion();
		} else if (type.equalsIgnoreCase("mp")) {
			potion = new MpPotion();
		}
		
		return potion;
	}
}
