package compound.ex2;

public class AttackCounter extends SimpleUnit {
	private SimpleUnit unit;
	private static int numberOfAttacks;

	public AttackCounter(SimpleUnit unit) {
		this.unit = unit;
	}
	
	public void performAttack() {
		unit.performAttack();
		numberOfAttacks++;
	}
	
	public void performMove() {
		unit.performMove();
	}
	
	public static int getAttacks() {
		return numberOfAttacks;
	}
	
	public void display() {
		unit.display();
	}
}
