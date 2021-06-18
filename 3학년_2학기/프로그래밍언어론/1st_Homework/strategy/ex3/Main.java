package strategy.ex3;

public class Main {
	public static void main(String[] args) {
		Unit medic   = new Medic();
		Unit warrior = new Warrior();
		Unit wraith  = new Wraith();
		
		medic.display();
		medic.performAttack();
		medic.performMove();
		
		System.out.println();
		
		warrior.display();
		warrior.performAttack();
		warrior.performMove();
		
		System.out.println();
		
		wraith.display();
		wraith.performAttack();
		wraith.performMove();
		
		System.out.println();
		
		Unit battleCruiser = new BattleCruiserAdapter(new BattleCruiser());
		battleCruiser.display();
		battleCruiser.performAttack();
	}
}
