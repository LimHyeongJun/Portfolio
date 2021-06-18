package iterator_and_composite.ex1;

public class LeagueOfLegends {
	public static void main(String[] args) {
		ChampionComponent adCarry = 
				new ChampionClass("AD Carry", "평타 원거리 딜러");
		ChampionComponent mage = 
				new ChampionClass("Mage", "스킬로 피해 입히는 마법사");
		ChampionComponent mageAssassin = 
				new ChampionClass("Mage Assassin", "마법사 암살자");  
		ChampionComponent tanker = 
				new ChampionClass("Tanker", "앞에서 몸빵 해주는 탱커");
		
		ChampionComponent allChampions = 
				new ChampionClass("All Champions", "All champions combined");
		
		allChampions.add(adCarry);
		allChampions.add(mage);
		allChampions.add(tanker);
		
		adCarry.add(new Champion("트리스타나", "대포 쏘는 요들"));
		adCarry.add(new Champion("자야", "깃털로 공격함"));
		adCarry.add(new Champion("애쉬", "얼음화살 날리는 여왕"));
		
		mage.add(new Champion("빅토르", "레이저를 쏘는 마법사"));
		mage.add(new Champion("직스", "폭탄을 던지는 마법사"));
		mage.add(new Champion("브랜드", "불로 공격하는 마법사"));
		
		mage.add(mageAssassin);
		mageAssassin.add(new Champion("피즈", "작살로 암살하는 마법사 암살자"));
		mageAssassin.add(new Champion("이블린", "평소에 은신하다가 암살하는 마법사 암살자"));
		
		tanker.add(new Champion("오른", "아이템 업글해주는 탱커"));
		tanker.add(new Champion("레오나", "cc기 많은 탱커"));
		tanker.add(new Champion("문도박사", "자체 체력회복이 뛰어난 탱커"));
		
		Gamer gamer = new Gamer(allChampions);
		
		gamer.printChampion();
	}
}
