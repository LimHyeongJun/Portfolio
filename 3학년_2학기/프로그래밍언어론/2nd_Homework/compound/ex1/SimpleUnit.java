package compound.ex1;

public abstract class SimpleUnit {
	private Attackable attackable;
	private Movable movable;
	
	public abstract void display();
	
	public void setAttackable(Attackable attackable) {
		this.attackable = attackable;
	}
	
	public void setMovable(Movable movable) {
		this.movable = movable;
	}
	
	public void performAttack() {
		attackable.attack();
	}
	
	public void performMove() {
		movable.move();
	}
}
