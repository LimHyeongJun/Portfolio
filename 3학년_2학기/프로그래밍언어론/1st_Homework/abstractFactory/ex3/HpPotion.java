package abstractFactory.ex3;

public class HpPotion extends Potion {
	PotionFactory potionFactory;
	
	public HpPotion(PotionFactory potionFactory) {
		this.potionFactory = potionFactory;
	}
	
	void prepare() {
		System.out.println("Preparing " + name);
		taste = potionFactory.createTaste();
		bottle = potionFactory.createBottle();
		amount = potionFactory.createAmount();
	}
}
