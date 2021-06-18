package abstractFactory.ex3;

public abstract class PotionStore {
	protected abstract Potion createPotion(String type, int level);
	
	public Potion orderPotion(String type, int level) {
		Potion potion = createPotion(type, level);
		
		potion.prepare();
		
		return potion;
	}
}
