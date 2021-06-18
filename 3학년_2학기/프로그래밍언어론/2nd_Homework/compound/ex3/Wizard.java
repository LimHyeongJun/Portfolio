package compound.ex3;

public class Wizard extends SimpleUnit {
	public Wizard() {
		setAttackable(new MagicAttack());
		setMovable(new MoveLand());
	}

	public void display() {
		System.out.println("This is a Wizard");
	}
}
