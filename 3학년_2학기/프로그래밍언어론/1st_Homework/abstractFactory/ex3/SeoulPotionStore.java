package abstractFactory.ex3;

public class SeoulPotionStore extends PotionStore {
	protected Potion createPotion(String type, int level) {
		Potion potion = null;
		PotionFactory potionFactory = new SeoulPotionFactory(type, level);
		
		if(type.equalsIgnoreCase("hp")) {
			potion = new HpPotion(potionFactory);
			potion.setName("Seoul's Hp potion " + level);
		} else if(type.equalsIgnoreCase("mp")) {
			potion = new MpPotion(potionFactory);
			potion.setName("Seoul's Mp potion " + level);
		}
		
		return potion;
	}
}
