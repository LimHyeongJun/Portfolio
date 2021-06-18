package compound.ex1;

public class Main {
	public static void main(String[] args) {
		SimpleUnit archer = new Archer();
		SimpleUnit warrior = new Warrior();
		SimpleUnit wizard = new Wizard();
		SimpleUnit battleCruiser = new BattleCruiserAdapter(new BattleCruiser());
		
		System.out.println("Simple Unit Simulator: With BattleCruiser Adapter\n-----");
		
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
	}
}
