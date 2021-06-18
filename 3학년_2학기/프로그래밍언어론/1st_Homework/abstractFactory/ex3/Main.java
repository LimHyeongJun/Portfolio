package abstractFactory.ex3;

public class Main {
	public static void main(String[] args) {
		System.out.println("--------Abstract factory pattern example 3--------");
		
		PotionStore seoulPotionStore = new SeoulPotionStore();
		PotionStore busanPotionStore = new BusanPotionStore();
		
		Potion seoulHp1 = seoulPotionStore.orderPotion("hp", 1);
		System.out.println(seoulHp1 + "\n");
		
		
		Potion seoulMp2 = seoulPotionStore.orderPotion("mp", 2);
		System.out.println(seoulMp2 + "\n");
		
		Potion seoulMp3 = seoulPotionStore.orderPotion("mp", 3);
		System.out.println(seoulMp3 + "\n");
		
		Potion busanMp1 = busanPotionStore.orderPotion("mp", 1);
		System.out.println(busanMp1 + "\n");
		
		Potion busanHp2 = busanPotionStore.orderPotion("hp", 2);
		System.out.println(busanHp2 + "\n");
		
		Potion busanHp3 = busanPotionStore.orderPotion("hp", 3);
		System.out.println(busanHp3 + "\n");
	}
}
