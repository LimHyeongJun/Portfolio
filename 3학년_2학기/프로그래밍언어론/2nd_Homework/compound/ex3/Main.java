package compound.ex3;

public class Main {
	public static void main(String[] args) {
		AbstractSimpleUnitFactory factory = new CountingSimpleUnitFactory();
		
		SimpleUnit archer = factory.createArcher();
		SimpleUnit warrior = factory.createWarrior();
		SimpleUnit wizard = factory.createWizard();
		SimpleUnit battleCruiser = new BattleCruiserAdapter(new BattleCruiser());
		
		System.out.println("Simple Unit Simulator: With Abstract Factory\n-----");

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
