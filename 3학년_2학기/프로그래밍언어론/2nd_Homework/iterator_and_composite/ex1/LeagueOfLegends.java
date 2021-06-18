package iterator_and_composite.ex1;

public class LeagueOfLegends {
	public static void main(String[] args) {
		ChampionComponent adCarry = 
				new ChampionClass("AD Carry", "��Ÿ ���Ÿ� ����");
		ChampionComponent mage = 
				new ChampionClass("Mage", "��ų�� ���� ������ ������");
		ChampionComponent mageAssassin = 
				new ChampionClass("Mage Assassin", "������ �ϻ���");  
		ChampionComponent tanker = 
				new ChampionClass("Tanker", "�տ��� ���� ���ִ� ��Ŀ");
		
		ChampionComponent allChampions = 
				new ChampionClass("All Champions", "All champions combined");
		
		allChampions.add(adCarry);
		allChampions.add(mage);
		allChampions.add(tanker);
		
		adCarry.add(new Champion("Ʈ����Ÿ��", "���� ��� ���"));
		adCarry.add(new Champion("�ھ�", "���з� ������"));
		adCarry.add(new Champion("�ֽ�", "����ȭ�� ������ ����"));
		
		mage.add(new Champion("���丣", "�������� ��� ������"));
		mage.add(new Champion("����", "��ź�� ������ ������"));
		mage.add(new Champion("�귣��", "�ҷ� �����ϴ� ������"));
		
		mage.add(mageAssassin);
		mageAssassin.add(new Champion("����", "�ۻ�� �ϻ��ϴ� ������ �ϻ���"));
		mageAssassin.add(new Champion("�̺�", "��ҿ� �����ϴٰ� �ϻ��ϴ� ������ �ϻ���"));
		
		tanker.add(new Champion("����", "������ �������ִ� ��Ŀ"));
		tanker.add(new Champion("������", "cc�� ���� ��Ŀ"));
		tanker.add(new Champion("�����ڻ�", "��ü ü��ȸ���� �پ ��Ŀ"));
		
		Gamer gamer = new Gamer(allChampions);
		
		gamer.printChampion();
	}
}
