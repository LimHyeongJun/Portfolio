package compound.ex3;

public class Archer extends SimpleUnit {
	public Archer() {
		setAttackable(new BowAttack());
		setMovable(new MoveLand());
	}
	
	public void display() {
		System.out.println("This is an archer");
	}
}
