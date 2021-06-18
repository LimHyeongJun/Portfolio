package compound.ex3;

public class Warrior extends SimpleUnit {
	public Warrior() {
		setAttackable(new SwordAttack());
		setMovable(new MoveLand());
	}

	public void display() {
		System.out.println("This is a Warrior");
	}
}