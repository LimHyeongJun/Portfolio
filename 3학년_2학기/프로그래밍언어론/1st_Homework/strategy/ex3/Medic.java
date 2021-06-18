package strategy.ex3;

public class Medic extends Unit {
	public Medic() {
		setAttackable(new NoAttack());
		setMovable(new MoveLand());
	}
	
	public void display() {
		System.out.println("This is Medic");
	}
}
