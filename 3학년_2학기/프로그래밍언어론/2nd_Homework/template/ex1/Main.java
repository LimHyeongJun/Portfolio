package template.ex1;

public class Main {
	public static void main(String[] args) {
		HpPotion hpPotion = new HpPotion();
		MpPotion mpPotion = new MpPotion();
		
		System.out.println("\nMaking Hp Potion...");
		hpPotion.prepareRecipe();
		
		System.out.println("\nMaking Mp Potion...");
		mpPotion.prepareRecipe();
	}
}
