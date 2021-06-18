package strategy.ex3;

public class Wraith extends Unit {
	public Wraith() {
		setAttackable(new GunAttack());
		setMovable(new MoveSky());
	}
	
	public void display() {
		System.out.println("This is Wraith");
	}
}
