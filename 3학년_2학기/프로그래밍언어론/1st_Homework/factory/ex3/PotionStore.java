package factory.ex3;

public class PotionStore {
	SimplePotionFactory factory;
	
	public PotionStore(SimplePotionFactory factory) {
		this.factory = factory;
	}
	
	public Potion orderPotion(String type) {
		Potion potion = null;
		
		potion = factory.createPotion(type);
		
		return potion;
	}
}
