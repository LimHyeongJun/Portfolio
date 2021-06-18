package compound.ex2;

public class Main {
	public static void main(String[] args) {
		SimpleUnit archer = new AttackCounter(new Archer());
		SimpleUnit warrior = new AttackCounter(new Warrior());
		SimpleUnit wizard = new AttackCounter(new Wizard());
		SimpleUnit battleCruiser = new BattleCruiserAdapter(new BattleCruiser());
		
		System.out.println("Simple Unit Simulator: With Decorator\n-----");
		
		archer.display();
		archer.performAttack();
		archer.performMove();
		System.out.println("-----");
		
		warrior.display();
		warrior.performAttack();
		warrior.performMove();
		System.out.println("-----");
		
		wizard.display();
		wizard.performAttack();
		wizard.performMove();
		System.out.println("-----");
		
		battleCruiser.display();
		battleCruiser.performAttack();
		battleCruiser.performMove();
		
		System.out.println("\nSimple Units attacked " 
				+ AttackCounter.getAttacks() + " times");
	}
}
