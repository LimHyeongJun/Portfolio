package abstractFactory.ex3;

public class BusanPotionStore extends PotionStore {
	protected Potion createPotion(String type, int level) {
		Potion potion = null;
		PotionFactory potionFactory = new BusanPotionFactory(type, level);
		
		if(type.equalsIgnoreCase("hp")) {
			potion = new HpPotion(potionFactory);
			potion.setName("Busan's Hp potion " + level);
		} else if(type.equalsIgnoreCase("mp")) {
			potion = new MpPotion(potionFactory);
			potion.setName("Busan's Mp potion " + level);
		}
		
		return potion;
	}
}
