package abstractFactory.ex3;

public class MpPotion extends Potion {
	PotionFactory potionFactory;
	
	public MpPotion(PotionFactory potionFactory) {
		this.potionFactory = potionFactory;
	}
	
	void prepare() {
		System.out.println("Preparing " + name);
		taste = potionFactory.createTaste();
		bottle = potionFactory.createBottle();
		amount = potionFactory.createAmount();
	}
}
