package factory.ex3;

public class Main {
	public static void main(String[] args) {
		System.out.println("--------Factory pattern example 3--------");
		
		SimplePotionFactory factory = new SimplePotionFactory();
		PotionStore store = new PotionStore(factory);
		
		Potion hpPotion[] = new Potion[10];
		Potion mpPotion[] = new Potion[10];
		
		for(int i = 0; i < 10; i++) {
			hpPotion[i] = store.orderPotion("hp");
			mpPotion[i] = store.orderPotion("mp");
		}
		
		System.out.println(hpPotion[0]);
		System.out.println(mpPotion[0]);
		
		for(int i = 0; i < 5; i++) {
			hpPotion[i].use();
			mpPotion[i].use();
		}
	}
}
